#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <iostream>

class HtmlEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    HtmlEditor(QWidget *parent = nullptr);
    HtmlEditor();
    ~HtmlEditor();

private:
    QFile html_file;
    void SaveFile();

public slots:
    void slSaveFileMenuBar();
    void slOpenFileMenuBar();

protected:
    void keyPressEvent(QKeyEvent* event) override;

};

#endif // HTMLEDITOR_H
