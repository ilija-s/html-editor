#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "search/editorsearch.h"
#include "html-parser/htmlparser.h"
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
    void searchForText();
    void toggleShowOrHideFindInProjectTab();
    void toggleShowOrHideMessagesTab();
    void parseHtmlFileAndDisplayMessages();

signals:
    void searchButtonClicked(const QString& searchString, QTextDocument *document);

private:
    Ui::MainWindow *ui;
    EditorSearch *_editorSearch;
    HTMLParser *_htmlParser;
    bool m_isBottomTabWidgetVisible{ true };
    void slFontSizeEnter();
    void slFontSizeChange();

};
#endif // MAINWINDOW_H
