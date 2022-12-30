#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "html-parser/htmlparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _editorSearch(new EditorSearch(this))
{
    ui->setupUi(this);
    ui->htmlEditor->SetNumberSideBar(ui->numberSideBar);
    ui->htmlEditor->setTabStopDistance(QFontMetricsF(ui->htmlEditor->font()).horizontalAdvance(' ') * 2);

    // Shortcuts
    auto showOrHideFindInProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+F", "Find in project")), this);
    auto showOrHideMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+M", "Open messages")), this);

    // Menu bar signals
    connect(ui->actionNew_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slNewFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionOpen_folder, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFolderMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, this, &MainWindow::parseHtmlFileAndDisplayMessages);
    connect(ui->actionSave_file_as, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveAsFileMenuBar);
    connect(ui->numberSideBar, &NumberSideBar::siPaintEvent, ui->htmlEditor, &HtmlEditor::slNumberBarPaintEvent);
    connect(this, &MainWindow::searchButtonClicked, _editorSearch, &EditorSearch::onSearchButtonClicked);
    connect(ui->leSearchInput , &QLineEdit::textChanged, this, &MainWindow::searchForText);
    connect(ui->treeView, &FileTreeView::doubleClicked, ui->treeView, &FileTreeView::slDoubleClicked);
    connect(ui->treeView, &FileTreeView::siDoubleClicked, ui->htmlEditor, &HtmlEditor::slTreeViewDoubleClicked);
    connect(ui->htmlEditor, &HtmlEditor::siOpenFolder, ui->treeView, &FileTreeView::SetFolder);
    connect(ui->htmlEditor, &HtmlEditor::siOpenFolder, this, &MainWindow::updateProjectFolder);
    connect(ui->htmlEditor, &HtmlEditor::siSetCursorAtLine, this, &MainWindow::setCursorAtLine);
    connect(ui->htmlEditor, &HtmlEditor::siFileExists, this, &MainWindow::updateWindowTitle);
    connect(ui->pbFindInProject, &QPushButton::clicked, this, &MainWindow::findInProjectClicked);
    connect(ui->lwLinesFound, &QListWidget::itemDoubleClicked, ui->htmlEditor, &HtmlEditor::slOpenFileAtLine);
    connect(showOrHideFindInProjectShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideFindInProjectTab);
    connect(showOrHideMessagesShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideMessagesTab);


    // Editor settings
    connect(ui->actionSettings_2, &QAction::triggered, this, &MainWindow::MainWindow::slEditorSettingsWindowOpen);

    // Menu bar shortcuts
    ui->actionNew_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    ui->actionOpen_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    ui->actionSave_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    ui->actionSave_file_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    this->setInitalStyleSheet();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _editorSearch;
}

void MainWindow::updateWindowTitle(QString filename)
{
    QStringList tokens = filename.split("/");
    this->setWindowTitle(tokens[tokens.length()-1] + " - HtmlEditor");
}

void MainWindow::searchForText()
{
    QString searchString = ui->leSearchInput->text();

    emit searchButtonClicked(searchString, ui->htmlEditor->document());
}

void MainWindow::slEditorSettingsWindowOpen(){
    editorSettingsWindow = new EditorSettings(this);
    editorSettingsWindow->show();

    connect(editorSettingsWindow, &EditorSettings::siFontSizeAccepted, this, &MainWindow::slFontSizeAccepted);
    connect(editorSettingsWindow, &EditorSettings::siThemeAccepted, this, &MainWindow::slThemeAccepted);
}

void MainWindow::slFontSizeAccepted(int fontSize, int ind){
    if(ind){
        ui->htmlEditor->fontSizeChange(fontSize);
    }
}

void MainWindow::updateProjectFolder(QString projectDirPath)
{
    m_projectDirPath = projectDirPath;
    m_project.deleteFileContents();
    m_project.loadFileContents(m_projectDirPath);
}

void MainWindow::setCursorAtLine(int linenumber)
{
    ui->htmlEditor->setFocus();
    QTextCursor cursor = ui->htmlEditor->textCursor();
    cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, linenumber - 1);
    ui->htmlEditor->setTextCursor(cursor);
}

void MainWindow::findInProjectClicked()
{
    ui->lwLinesFound->clear();
    if (m_projectDirPath.isEmpty()) {
        qDebug() << "Project directory is not set.";
        return;
    }
    QString needle = ui->leFindInProjectSearchQuery->text();

    foreach (TextFile textfile, m_project.textFiles()) {
        foreach (LineData data, textfile.find(needle.toStdString())) {
            QString content(data.content.trimmed());
            QString text(data.filename + ": " + std::to_string(data.lineNumber).c_str() + "\t" + content);
            QListWidgetItem* item = new QListWidgetItem(text);
            item->setWhatsThis(data.absoluteFilePath);
            ui->lwLinesFound->addItem(item);
       }
    }
}

void MainWindow::parseHtmlFileAndDisplayMessages()
{
    // In the future this should underscore words that have errors

    // Clear all previous items
    ui->lwEditorMessages->clear();

    std::string textDocument = ui->htmlEditor->document()->toPlainText().toStdString();
    std::unique_ptr<HTMLParser> htmlParser = std::make_unique<HTMLParser>(textDocument);

    // Add items to QListWidget
    QList<QVariant> listOfMessages = htmlParser.get()->getMessages().toList();
    // TODO: This looks really bad, extract to a method or try using std::transform
    for (int i = 0; i < listOfMessages.length(); ++i) {
        QMap map = listOfMessages[i].toMap();
        QString type = map["type"].toString();
        QString message = map["message"].toString();
        QString lastLine = map["lastLine"].toString();
        QString text = "Line: " + lastLine + " Message: " + message;
        QIcon icon = QIcon(":/images/" + type + ".png");
        QListWidgetItem* item = new QListWidgetItem(icon, text);
        ui->lwEditorMessages->addItem(item);
    }
}

void MainWindow::toggleShowOrHideFindInProjectTab()
{
    m_isBottomTabWidgetVisible = !m_isBottomTabWidgetVisible;
    if (m_isBottomTabWidgetVisible) {
        ui->tabWidget->setVisible(true);
        ui->searchTab->setFocus();
    } else {
        ui->tabWidget->setVisible(false);
    }
}

void MainWindow::toggleShowOrHideMessagesTab()
{
    m_isBottomTabWidgetVisible = !m_isBottomTabWidgetVisible;
    if (m_isBottomTabWidgetVisible) {
        ui->tabWidget->setVisible(true);
        ui->messageTab->setFocus();
    } else {
        ui->tabWidget->setVisible(false);
    }
}

void MainWindow::slThemeAccepted(int ind){
    if(ind == 1){
        this->setStyleSheet(styleSheetInital);
        ui->htmlEditor->setStyleSheet(styleSheetInitalHTML);
        ui->pbFindInProject->setStyleSheet(styleSheetInitalFindIn);
        ui->tabWidget->setStyleSheet(styleSheetInitalTab);
        ui->treeView->setStyleSheet(styleSheetInitalTreeView);
        ui->leFindInProjectSearchQuery->setStyleSheet(styleSheetInitalleFindIn);
        ui->leSearchInput->setStyleSheet(styleSheetleSearch);
    } else if(ind == 2){
        this->setStyleSheet("background-color: #4F4B4B;  color: white; border-color: black; border-style: solid white;\
            border-width: thin;");
        ui->htmlEditor->setStyleSheet("background-color: #352F2F;  color: white; font-weight: bold; border-color: white; \
            border-style: solid black; border-width: thin;");

        QString treeViewStyle = "QTreeView {\
               background-color: #352F2F;\
               color: white\
            }\
        QTreeView::item:selected:active{\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\
        }";

        ui->treeView->setStyleSheet(treeViewStyle);

        QString tabStyle = "QTabBar::tab {\
                background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #757575, stop: 1 #352F2F);\
                border: solid white;\
                border-top-left-radius: 10px;\
                border-top-right-radius: 10px;\
                min-width: 8ex;\
                padding: 2px;\
                color: white;\
            }\
                QTabWidget {\
                    border: 2px solid white;\
                    background-color: #352F2F\
                    color: black;\
                }\
                QTabBar::tab:selected {\
                    border-color: #080808;\
                    background-color: #352F2F;\
                    border-bottom-style: transparent; \
                }\
                \
                QTabBar::tab:!selected {\
                    margin-top: 2px;\
                }";
        ui->tabWidget->setStyleSheet(tabStyle);
        ui->lwLinesFound->setStyleSheet("QListWidget { border: 1px solid black; }");

        QString pbFindInProjectStyle = "QPushButton:pressed {\
                background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                  stop: 0 #dadbde, stop: 1 #f6f7fa);\
                } \
        QPushButton {\
            border: solid white;\
            border-width: thin;\
            border-radius: 6px;\
            background-color: #A3A0A0;\
        }";

       ui->pbFindInProject->setStyleSheet(pbFindInProjectStyle);
       ui->leFindInProjectSearchQuery->setStyleSheet("QLineEdit {\
                                        border-color: white;\
                                        border-style: solid;\
                                        border-width: thin;\
                                        background: #A3A0A0;}");

        QString searchStyle = "QLineEdit {\
                border: 2px solid white;\
                color: white;\
                background: #4F4B4B;\
            }";
        ui->leSearchInput->setStyleSheet(searchStyle);


        ui->lwEditorMessages->setStyleSheet("QLineWidget { border-color: white;\
                                            border-style: solid;\
                                            background: #A3A0A0;}");

        this->editorSettingsWindow->changeStyle();

        this->repaint();
    }
}

void MainWindow::setInitalStyleSheet(){
    this->styleSheetInital = this->styleSheet();
    styleSheetInitalHTML = ui->htmlEditor->styleSheet();
    styleSheetInitalFindIn = ui->pbFindInProject->styleSheet();
    styleSheetInitalTab = ui->tabWidget->styleSheet();
    styleSheetInitalTreeView = ui->treeView->styleSheet();
    styleSheetleSearch = ui->leSearchInput->styleSheet();
}

