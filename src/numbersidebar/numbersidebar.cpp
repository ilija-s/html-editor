#include "numbersidebar.h"

NumberSideBar::NumberSideBar(QWidget *parent)
    : QWidget{parent}
{

auto
NumberSideBar::sizeHint() const -> QSize
{
    return QSize(width, 1080);
}

void NumberSideBar::paintEvent(QPaintEvent *event)
{
    emit siPaintEvent(event);
}
