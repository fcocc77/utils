#include <qt.hpp>

namespace qt
{
    void set_icon(QPushButton *button, QString name, int size)
    {
        QString path = "resources/images/" + name + ".png";
        QPixmap pixmap(path);
        QIcon ButtonIcon(pixmap);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(size, size));
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

    QString float_to_string(float number, int decimals)
    {
        return QString::number(qRound(number * 100) / 100.0, 'f', decimals);
    }

    bool alt()
    {
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::AltModifier))
            return true;
        else
            return false;
    }

    bool shift()
    {
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
            return true;
        else
            return false;
    }

    float distance_points(QPointF a, QPointF b)
    {
        return sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2));
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