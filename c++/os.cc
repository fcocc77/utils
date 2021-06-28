#include "os.h"
#include <QDebug>
#include <QString>

namespace os
{

void system(QString cmd)
{
    if (_win32)
        cmd = "\"" + cmd + "\"";

    std::system(cmd.toStdString().c_str());
}

void copy(QString src, QString dst)
{
    if (QFile::exists(dst))
        QFile::remove(dst);

    QFile::copy(src, dst);
}

void copydir(QString src, QString dst)
{
    os::sh("cp -rf \"" + src + "\" \"" + dst + "\"");
}

void move(QString src, QString dst)
{
    copymove(src, dst, false);
}

void copymove(QString src, QString dst, bool copy)
{

    QString cmd;
    QString cp;
    bool execute = true;

    if (_win32)
    {
        src = src.replace("/", "\\");
        dst = dst.replace("/", "\\");

        if (os::isfile(src))
        {
            if (copy)
                cp = "copy";
            else
                cp = "move";
        }

        else if (os::isdir(src))
        {
            if (copy)
                cp = "echo d | xcopy";
            else
                cp = "move";
        }

        else
        {
            qDebug() << "file or dir not found.";
            execute = false;
        }
    }

    else
    {
        if (os::isfile(src))
        {
            if (copy)
                cp = "cp";
            else
                cp = "mv";
        }
        else if (os::isdir(src))
        {
            if (copy)
                cp = "cp -rf";
            else
                cp = "mv -rf";
        }

        else
        {
            qDebug() << "file or dir not found.";
            execute = false;
        }
    }

    cmd = cp + " \"" + src + "\" \"" + dst + "\"";

    if (execute)
    {
        os::sh(cmd);
    }
}

void remove(QString _file)
{
    QFile file(_file);
    file.remove();
    QDir dir(_file);
    dir.removeRecursively();
}

void rename(QString src, QString dst)
{
    std::rename(src.toStdString().c_str(), dst.toStdString().c_str());
}

QString dirname(QString file)
{
    QFileInfo _file(file);
    return _file.absolutePath();
}

QString basename(QString file)
{
    return file.split("/").last();
}

bool isfile(QString file)
{
    return QFile(file).exists();
}

bool isdir(QString dir)
{
    return QDir(dir).exists();
}

void makedirs(QString dir)
{
    if (!isdir(dir))
        QDir(dir).mkpath(dir);
}

void makedir(QString dir)
{
    if (!isdir(dir))
        QDir(dir).mkdir(dir);
}

#ifdef _WIN32
void KillProcessTree(DWORD myprocID)
{

    PROCESSENTRY32 pe;

    memset(&pe, 0, sizeof(PROCESSENTRY32));
    pe.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (::Process32First(hSnap, &pe))
    {
        do // Recursion
        {
            if (pe.th32ParentProcessID == myprocID)
                KillProcessTree(pe.th32ProcessID);
        } while (::Process32Next(hSnap, &pe));
    }

    // kill the main process
    HANDLE hProc = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, myprocID);

    if (hProc)
    {
        ::TerminateProcess(hProc, 1);
        ::CloseHandle(hProc);
    }
}
#endif

void kill(int pid, bool force)
{
    if (_linux)
    {
        vector<int> pids = {pid};
        vector<int> childs = {pid};

        while (1)
        {
            //------------------------------
            for (auto child : childs)
            {
                string result =
                    sh("ps --ppid " + QString::number(child)).toStdString();
                istringstream read(result);
                string line;
                childs = {};
                while (getline(read, line))
                {
                    try
                    {
                        childs.push_back(stoi(line));
                    } catch (exception &e)
                    {
                    }
                }
            }
            //------------------------------
            if (not childs.empty())
            {
                for (auto c : childs)
                {
                    pids.push_back(c);
                }
            }

            else
            {
                break;
            }
            //------------------------------
        }

        for (auto p : pids)
            if (force)
                sh("kill -9 " + QString::number(p));
            else
                sh("kill " + QString::number(p));
    }

#ifdef _WIN32
    KillProcessTree(pid);
#endif
}

QStringList listdir(QString folder, bool recursive, bool onlyname)
{
    QStringList list_dir;
    QDir root = folder;

    auto append = [&](QString file) {
        QString name = basename(file);

        if (onlyname)
            file = name;

        if ((name != ".") and (name != ".."))
            list_dir.push_back(file);
    };

    if (recursive)
    {
        QDirIterator it(root, QDirIterator::Subdirectories);
        while (it.hasNext())
            append(it.next());
    }
    else
    {
        QDirIterator it(root);
        while (it.hasNext())
            append(it.next());
    }

    return list_dir;
}

QString sh(QString cmd, bool error)
{
    QProcess proc;
    proc.start(cmd);
    proc.waitForFinished(-1);
    QString output;
    if (error)
        output =
            proc.readAllStandardOutput() + "\n" + proc.readAllStandardError();
    else
        output = proc.readAllStandardOutput();

    proc.close();

    return output;
}

const QString hostName()
{
    return QHostInfo::localHostName();
}

const QString ip()
{
    QString _ip;
    int i = 0;
    for (auto ip : QNetworkInterface::allAddresses())
    {
        _ip = ip.toString();
        QString first = _ip.split(".")[0];
        if (first == "192")
            return _ip;
        i++;
    }
    return "";
}

QString get_user()
{
    static QString user_name;

    if (user_name.isEmpty())
    {
        user_name = os::sh(
                "sh -c \"loginctl list-sessions | awk /1/'{print $3; exit}'\"");

        user_name = user_name.simplified();
    }

    return user_name;
}

QString get_home()
{
    return "/home/" + get_user();
}

const QString mac()
{
    auto interfaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < interfaces.count(); i++)
    {
        QString _mac = interfaces[i].hardwareAddress();
        QString _ip;

        // encuentra la ip correspondiente a la interface
        QList<QNetworkAddressEntry> address = interfaces[i].addressEntries();
        if (!address.empty())
            _ip = address[0].ip().toString();

        // retorna la direccion mac que corresponde a la ip
        if (_ip == ip())
            return _mac;
    }

    return "";
}

void back(QString cmd)
{
    QProcess pro;
    pro.startDetached(cmd);
    pro.waitForStarted();
}

const QString user()
{

    if (_linux)
    {
        // get user
        QString get_user = "grep '/bin/bash' /etc/passwd | cut -d':' -f1";
        return os::sh(get_user).split("\n")[1];
        //------------------------------------------------------
    }
    else
    {
        return "";
    };
}

} // namespace os
