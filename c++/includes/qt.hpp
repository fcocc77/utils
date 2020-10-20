#ifndef QT_HPP
#define QT_HPP

#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

#include <util.hpp>

namespace qt
{
    void set_icon(QPushButton *button, QString path);
    void add_widget(QWidget *parent, QWidget *widget);

} // namespace qt

#endif //QT_HPP