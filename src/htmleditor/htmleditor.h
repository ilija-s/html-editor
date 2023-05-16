#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include "src/numbersidebar/numbersidebar.h"
#include "src/syntaxhighlighting/htmlsyntaxhighlighter.h"
#include <QFile>
#include <QListWidgetItem>
#include <QObject>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QWidget>
#include <iostream>

class HtmlEditor : public QPlainTextEdit
{
  Q_OBJECT
public:
  HtmlEditor(QWidget* parent = nullptr);
  ~HtmlEditor();
  void SetNumberSideBar(NumberSideBar* sb);
  QString fileName();
  NumberSideBar* getNumberBar();
  void fontSizeChange(int mainSize);

private:
  QFile html_file;
  QString file_name;
  NumberSideBar* number_bar;
  HtmlSyntaxHighlighter* highlighter;
  void NewFile();
  void SaveFile();
  void SaveAsFile();
  void OpenFile(QString path = "");
  void OpenFolder();
  int NumberBarWidth();
  void UpdateNumberBarWidth();
  void UpdateNumberBar(const QRect& rect, int dy);

  int size = 10;

protected:
  void resizeEvent(QResizeEvent* event) override;

signals:
  void siOpenFolder(QString dir_path);
  void siFileExists(QString file_path);
  void siTreeViewFolder(QString dir_path);
  void siSetCursorAtLine(int linenumber);
  void siFileSaved(QString dummy);
public slots:
  void slTreeViewDoubleClicked(const QString& path);
  void slNewFileMenuBar();
  void slOpenFileMenuBar();
  void slOpenFolderMenuBar();
  void slSaveFileMenuBar();
  void slSaveAsFileMenuBar();
  void slNumberBarPaintEvent(QPaintEvent* event);
  void slOpenFileAtLine(QListWidgetItem* item);
};

#endif // HTMLEDITOR_H
