#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _editorSearch(new EditorSearch(this))
    , _htmlParser(new HTMLParser())
{
    ui->setupUi(this);
    ui->htmlEditor->SetNumberSideBar(ui->numberSideBar);

    // Shortcuts
    auto showOrHideFindInProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+F", "Find in project")), this);
    auto showOrHideMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+M", "Open messages")), this);

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

    _htmlParser->loadJsonData();

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

