#include <qt.h>

namespace qt
{
    void set_icon(QPushButton *button, QString name, int size)
    {
        QString path = "resources/images/" + name + ".png";
        if (name.contains("/"))
            path = name;

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

    bool control()
    {
        if (QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
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

    void focus_under_mouse(QWidget *obj)
    {
        // esto se usa en algunos widget para que cuando el cursor este sobre el widget
        // lo deje a foco, y asi los shortcut de cada widget, funcionen de inmediato, y asi
        // no tengamos que darle click al widget para darle foco; con excepción al
        // widget que esta en foco de tipo 'QLineEdit' no cambia el foco.
        if (!obj->hasFocus())
        {
            if (qApp->widgetAt(QCursor::pos()) == obj)
            {
                QWidget *focus_widget = qApp->focusWidget();
                if (focus_widget)
                {
                    QString class_name = qApp->focusWidget()->metaObject()->className();
                    if (class_name != "QLineEdit" && class_name != "QCodeEditor")
                        obj->setFocus();
                }
            }
        }
    }

} // namespace qt
