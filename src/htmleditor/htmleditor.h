#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <iostream>
#include <QTextStream>

class HtmlEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    HtmlEditor(QWidget *parent = nullptr);
    HtmlEditor();
    ~HtmlEditor();

private:
    QFile html_file;
    QString file_name;
    void SaveFile();
    void SaveAsFile();
    void OpenFile();

public slots:
    void slOpenFileMenuBar();
    void slSaveFileMenuBar();
    void slSaveAsFileMenuBar();

protected:
    void keyPressEvent(QKeyEvent* event) override;

};

#endif // HTMLEDITOR_H
