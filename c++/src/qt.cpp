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

} // namespace qt