#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "editorsettings/editorsettings.h"
#include "project/project.h"
#include "search/editorsearch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
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
    void findInProjectClicked();
    void updateProjectFolder(QString projectDirPath);
    void setCursorAtLine(int linenumber);
    void updateWindowTitle(QString filename);

   signals:
    void searchButtonClicked(const QString &searchString, QTextDocument *document);

   private:
    Ui::MainWindow *ui;
    EditorSearch *_editorSearch;
    QString m_projectDirPath;
    Project m_project;

    EditorSettings *editorSettingsWindow;

    bool m_isBottomTabWidgetVisible{true};
};
#endif  // MAINWINDOW_H
