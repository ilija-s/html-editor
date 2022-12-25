#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include "src/numbersidebar/numbersidebar.h"

class HtmlEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    HtmlEditor(QWidget *parent = nullptr);
    ~HtmlEditor();
    void SetNumberSideBar(NumberSideBar* sb);

    void fontSizeChange(int mainSize);

private:
    QFile html_file;
    QString file_name;
    NumberSideBar* number_bar;
    void NewFile();
    void SaveFile();
    void SaveAsFile();
    void OpenFile(QString path = "");
    void OpenFolder();
    int NumberBarWidth();
    void UpdateNumberBarWidth();
    void UpdateNumberBar(const QRect &rect, int dy);

    int size = 10;

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void siOpenFolder(QString dir_path);
    void siFileExists(QString file_path);
    void siTreeViewFolder(QString dir_path);
public slots:
    void slTreeViewDoubleClicked(const QString& path);
    void slNewFileMenuBar();
    void slOpenFileMenuBar();
    void slOpenFolderMenuBar();
    void slSaveFileMenuBar();
    void slSaveAsFileMenuBar();
    void slNumberBarPaintEvent(QPaintEvent *event);

};

#endif // HTMLEDITOR_H
