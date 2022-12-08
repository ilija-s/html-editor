#ifndef NUMBERSIDEBAR_H
#define NUMBERSIDEBAR_H

#include <QWidget>

class NumberSideBar : public QWidget
{
    Q_OBJECT
public:
    NumberSideBar(QWidget *parent);
    QSize sizeHint() const override;

    int width;

signals:
    void siPaintEvent(QPaintEvent* event);

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif // NUMBERSIDEBAR_H
