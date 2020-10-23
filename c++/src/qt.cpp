#include <qt.hpp>

namespace qt
{
    void set_icon(QPushButton *button, QString path, QSize size)
    {
        QPixmap pixmap(path);
        QIcon ButtonIcon(pixmap);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(size));
    }

    void add_widget(QWidget *parent, QWidget *widget)
    {
        QLayout *layout;
        if (parent->layout() == NULL)
        {
            layout = new QVBoxLayout();
            layout->setContentsMargins(0, 0, 0, 0);
            parent->setLayout(layout);
        }
        else
        {
            layout = parent->layout();
        }

        widget->setParent(parent);
        parent->layout()->addWidget(widget);
    }

    QJsonArray list_to_array(QStringList list)
    {
        QJsonArray array;
        for (QString item : list)
        {
            array.push_back(item);
        }

        return array;
    }

    QStringList array_to_list(QJsonArray array)
    {
        QStringList list;
        for (QJsonValue item : array)
        {
            list.push_back(item.toString());
        }

        return list;
    }

} // namespace qt