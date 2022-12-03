#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slSetInputFileNameVisible();
    void slInputFileNameRead();
    void slFontSizeEnter();
    void slFontSizeChange();

signals:
    void siInputFileNameProccesed(const QString& s);

private:
    Ui::MainWindow *ui;
    int size = 10;


};
#endif // MAINWINDOW_H
