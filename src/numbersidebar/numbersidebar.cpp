#include "numbersidebar.h"

NumberSideBar::NumberSideBar(QWidget *parent) : QWidget{parent} {}

QSize NumberSideBar::sizeHint() const { return QSize(width, 1080); }

void NumberSideBar::paintEvent(QPaintEvent *event) { emit siPaintEvent(event); }
