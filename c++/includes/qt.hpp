#ifndef QT_HPP
#define QT_HPP

#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QJsonArray>
#include <QStringList>

#include <util.hpp>

namespace qt
{
    void set_icon(QPushButton *button, QString path, QSize size = QSize(20, 20));
    void add_widget(QWidget *parent, QWidget *widget);
    QJsonArray list_to_array(QStringList list);
    QStringList array_to_list(QJsonArray array);

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