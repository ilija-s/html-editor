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

public slots:
    void slOpenFileMenuBar(const QString& file_name);
    void slSaveFileMenuBar();

protected:
    void keyPressEvent(QKeyEvent* event) override;

};

#endif // HTMLEDITOR_H
