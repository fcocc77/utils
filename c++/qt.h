#ifndef QT_HPP
#define QT_HPP

#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QStringList>
#include <QShortcut>
#include <QGuiApplication>
#include <QApplication>
#include <QLineEdit>
#include <QStyle>
#include <QWidget>

#include <util.h>

namespace qt
{
    void set_icon(QPushButton *button, QString path, int size = 30);
    void add_widget(QWidget *parent, QWidget *widget);
    QJsonArray list_to_array(QStringList list);
    QStringList array_to_list(QJsonArray array);
    bool alt();
    bool control();
    bool shift();
    float distance_points(QPointF a, QPointF b);
    QString float_to_string(float number, int decimals);
    void focus_under_mouse(QWidget *obj);

    template <class T1, class T2>
	void set_property(T1 *widget, QString name, T2 value)
	{
		widget->setProperty(name.toStdString().c_str(), value);
		widget->style()->unpolish(widget);
		widget->style()->polish(widget);
	}

    template <class T>
    QList<T> reverse(QList<T> list)
    {
        // revierte una lista, retornando una lista nueva
        QList<T> _list = list;
        std::reverse(begin(_list), end(_list));

        return _list;
    }

    template <class T, typename Func>
    void shortcut(QString key, T *obj, Func lambda_func)
    {
        QShortcut *_shortcut = new QShortcut(QKeySequence(key), obj);
        QObject::connect(_shortcut, &QShortcut::activated, obj, lambda_func);
    }

    template <class T>
    void insert_json_deep(QJsonObject *object, QStringList keys, T value)
    {
        // retorna el ultimo objeto
        auto get_deep = [=](int deep) {
            QJsonObject base = *object;
            for (int i = 0; i < deep; i++)
            {
                QString key = keys[i];
                base = base.value(key).toObject();
            }

            return base;
        };
        //
        //

        int count = keys.length();

        if (count == 1)
        {
            object->insert(keys[0], value);
        }

        else if (count == 2)
        {
            QJsonObject deep0 = get_deep(1);
            deep0.insert(keys[1], value);
            object->insert(keys[0], deep0);
        }

        else if (count == 3)
        {
            QJsonObject deep1 = get_deep(2);
            deep1.insert(keys[2], value);

            QJsonObject deep0 = get_deep(1);
            deep0.insert(keys[1], deep1);
            object->insert(keys[0], deep0);
        }

        else if (count == 4)
        {
            QJsonObject deep2 = get_deep(3);
            deep2.insert(keys[3], value);

            QJsonObject deep1 = get_deep(2);
            deep1.insert(keys[2], deep2);

            QJsonObject deep0 = get_deep(1);
            deep0.insert(keys[1], deep1);
            object->insert(keys[0], deep0);
        }

        else if (count == 5)
        {
            QJsonObject deep3 = get_deep(4);
            deep3.insert(keys[4], value);

            QJsonObject deep2 = get_deep(3);
            deep2.insert(keys[3], deep3);

            QJsonObject deep1 = get_deep(2);
            deep1.insert(keys[2], deep2);

            QJsonObject deep0 = get_deep(1);
            deep0.insert(keys[1], deep1);
            object->insert(keys[0], deep0);
        }
    }

} // namespace qt

#endif //QT_HPP
