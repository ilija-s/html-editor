#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editorsettings/editorsettings.h"
#include "search/editorsearch.h"
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

    void slEditorSettingsWindowOpen();
    void slFontSizeAccepted(int fontSize, int ind);

    void toggleShowOrHideFindInProjectTab();
    void toggleShowOrHideMessagesTab();
    void parseHtmlFileAndDisplayMessages();


signals:
    void searchButtonClicked(const QString& searchString, QTextDocument *document);

private:
    Ui::MainWindow *ui;
    EditorSearch *_editorSearch;

    EditorSettings *editorSettingsWindow;


    bool m_isBottomTabWidgetVisible{ true };

};
#endif // MAINWINDOW_H
