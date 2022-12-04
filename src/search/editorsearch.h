#ifndef EDITORSEARCH_H
#define EDITORSEARCH_H

#include <QWidget>

#include <src/htmleditor/htmleditor.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QPlainTextEdit;
QT_END_NAMESPACE

class EditorSearch : public QWidget
{
    Q_OBJECT

public:
    EditorSearch(QWidget *parent = nullptr);

public slots:
    void on_pbFind_clicked();

private:
    QPushButton *findButton;
    HtmlEditor *text;
    QLineEdit *lineEdit;
};

#endif // EDITORSEARCH_H
