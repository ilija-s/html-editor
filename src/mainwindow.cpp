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

    // Shortcuts
    auto showOrHideFindInProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+F", "Find in project")), this);
    auto showOrHideMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+M", "Open messages")), this);
    auto parseHtmlFileAndDisplayMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+P", "Parse document")), this);

    // Menu bar signals
    connect(ui->actionNew_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slNewFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionSave_file_as, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveAsFileMenuBar);
    connect(ui->numberSideBar, &NumberSideBar::siPaintEvent, ui->htmlEditor, &HtmlEditor::slNumberBarPaintEvent);
    connect(this, &MainWindow::searchButtonClicked, _editorSearch, &EditorSearch::onSearchButtonClicked);
    connect(ui->leSearchInput , &QLineEdit::textChanged, this, &MainWindow::searchForText);
    connect(showOrHideFindInProjectShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideFindInProjectTab);
    connect(showOrHideMessagesShortcut , &QShortcut::activated, this, &MainWindow::toggleShowOrHideMessagesTab);
    connect(parseHtmlFileAndDisplayMessagesShortcut , &QShortcut::activated, this, &MainWindow::parseHtmlFileAndDisplayMessages);


    ui->fontSize->setVisible(false);
    // Editor settings signals
    connect(ui->actionFont_size, &QAction::triggered, this, &MainWindow::slFontSizeEnter);
    connect(ui->pbfontSize, &QAbstractButton::clicked, this, &MainWindow::slFontSizeChange);

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

void MainWindow::slFontSizeEnter()
{
     ui->fontSize->setVisible(true);
     ui->lnotEntered->setVisible(false);
}

void MainWindow::slFontSizeChange()
{
    bool flag;
    int tmp = ui->lEfontSize->text().trimmed().toInt(&flag);
    ui->lEfontSize->clear();

    if(!flag || tmp <= 0){
       ui->lnotEntered->setVisible(true);
       return;
    }

    ui->fontSize->setVisible(false);
    ui->htmlEditor->fontSizeChange(tmp);
}

void MainWindow::parseHtmlFileAndDisplayMessages()
{
    // In the future this should underscore words that have errors, also this
    // method should work async

    // Clear all previous items
    ui->lwEditorMessages->clear();

    std::unique_ptr<HTMLParser> htmlParser = std::make_unique<HTMLParser>();
    htmlParser.get()->loadJsonData(ui->htmlEditor->document()->toPlainText().toStdString());

    // Add items to QListWidget
    QList<QVariant> listOfMessages = htmlParser.get()->getMessages().toList();
    QList<QString> list;
    // TODO: This looks really bad, extract to a method or try using std::transform
    for (int i = 0; i < listOfMessages.length(); ++i) {
        QMap map = listOfMessages[i].toMap();
        QString message = map["message"].toString();
        QString type = map["type"].toString();
        QString lastLine = map["lastLine"].toString();
        QString str = "Type: " + type + ". Line: " + lastLine + ". Message: " + message;
        list.append(str);
    }
    ui->lwEditorMessages->addItems(list);
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

