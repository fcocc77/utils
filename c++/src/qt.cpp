#include <qt.hpp>

namespace qt
{
    void set_icon(QPushButton *button, QString path)
    {
        QPixmap pixmap(path);
        QIcon ButtonIcon(pixmap);
        button->setIcon(ButtonIcon);
        button->setIconSize(pixmap.rect().size());
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

        parent->layout()->addWidget(widget);
    }

} // namespace qt