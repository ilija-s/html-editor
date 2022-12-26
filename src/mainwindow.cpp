#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "html-parser/htmlparser.h"
#include "project/project.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _editorSearch(new EditorSearch(this))
{
    ui->setupUi(this);
    ui->htmlEditor->SetNumberSideBar(ui->numberSideBar);

    // Shortcuts
    auto showOrHideFindInProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+F", "Find in project")), this);
    auto showOrHideMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+M", "Open messages")), this);
    auto parseHtmlFileAndDisplayMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+P", "Parse document")), this);

    // Menu bar signals
    connect(ui->actionNew_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slNewFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionOpen_folder, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFolderMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionSave_file_as, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveAsFileMenuBar);
    connect(ui->numberSideBar, &NumberSideBar::siPaintEvent, ui->htmlEditor, &HtmlEditor::slNumberBarPaintEvent);
    connect(this, &MainWindow::searchButtonClicked, _editorSearch, &EditorSearch::onSearchButtonClicked);
    connect(ui->leSearchInput , &QLineEdit::textChanged, this, &MainWindow::searchForText);
    connect(showOrHideFindInProjectShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideFindInProjectTab);
    connect(showOrHideMessagesShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideMessagesTab);
    connect(parseHtmlFileAndDisplayMessagesShortcut , &QShortcut::activated, this, &MainWindow::parseHtmlFileAndDisplayMessages);
    connect(ui->htmlEditor, &HtmlEditor::siFileExists, ui->treeView, &FileTreeView::SetModel);
    connect(ui->treeView, &FileTreeView::doubleClicked, ui->treeView, &FileTreeView::slDoubleClicked);
    connect(ui->treeView, &FileTreeView::siDoubleClicked, ui->htmlEditor, &HtmlEditor::slTreeViewDoubleClicked);
    connect(ui->htmlEditor, &HtmlEditor::siOpenFolder, ui->treeView, &FileTreeView::SetFolder);
    connect(ui->pbFindInProject, &QPushButton::clicked, this, &MainWindow::findInProjectClicked);


    // Editor settings
    connect(ui->actionSettings_2, &QAction::triggered, this, &MainWindow::MainWindow::slEditorSettingsWindowOpen);

    // Menu bar shortcuts
    ui->actionNew_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    ui->actionOpen_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    ui->actionSave_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    ui->actionSave_file_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _editorSearch;
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
}

void MainWindow::slFontSizeAccepted(int fontSize, int ind){
    if(ind){
        ui->htmlEditor->fontSizeChange(fontSize);
    }
}

void MainWindow::findInProjectClicked()
{
    // This is not optimal solution
    // Read directory path from current file
    QFileInfo fileinfo(ui->htmlEditor->fileName());
    QDir absoluteDir = fileinfo.absoluteDir();
    QString absoluteFilePath = absoluteDir.absolutePath();
    QString needle = ui->leFindInProjectSearchQuery->text();
    qDebug() << "Needle: " << needle;

    // This should maybe be a member variable
    Project project;
    project.loadFileContents(absoluteFilePath);

    foreach (TextFile textfile, project.fileContents()) {
        foreach (LineData data, textfile.find(needle.toStdString())) {
            QString content(data.content.trimmed());
            QString text(data.filename + ": " + std::to_string(data.lineNumber).c_str() + "\t" + content);
            QListWidgetItem* item = new QListWidgetItem(text);
            ui->lwLinesFound->addItem(item);
       }
    }
}

void MainWindow::parseHtmlFileAndDisplayMessages()
{
    // In the future this should underscore words that have errors, also this
    // method should work async

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

