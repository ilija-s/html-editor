#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include "src/numbersidebar/numbersidebar.h"
#include "src/htmlsyntaxhighlighter.h"

class HtmlEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    HtmlEditor(QWidget *parent = nullptr);
    ~HtmlEditor();
    void SetNumberSideBar(NumberSideBar* sb);

private:
    QFile html_file;
    QString file_name;
    NumberSideBar* number_bar;
    HtmlSyntaxHighlighter* highlighter;
    void NewFile();
    void SaveFile();
    void SaveAsFile();
    void OpenFile();
    int NumberBarWidth();
    void UpdateNumberBarWidth();
    void UpdateNumberBar(const QRect &rect, int dy);

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void slNewFileMenuBar();
    void slOpenFileMenuBar();
    void slSaveFileMenuBar();
    void slSaveAsFileMenuBar();
    void slNumberBarPaintEvent(QPaintEvent *event);

};

#endif // HTMLEDITOR_H
