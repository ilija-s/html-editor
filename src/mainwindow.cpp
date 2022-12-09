#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _editorSearch(new EditorSearch(this))
{
    ui->setupUi(this);
    ui->pbFileName->setVisible(false);
    ui->inputFileName->setVisible(false);

    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::slSetInputFileNameVisible);
    connect(ui->pbFileName, &QAbstractButton::clicked, this, &MainWindow::slInputFileNameRead);
    connect(this, &MainWindow::siInputFileNameProccesed, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(this, &MainWindow::searchButtonClicked, _editorSearch, &EditorSearch::onSearchButtonClicked);
    connect(ui->leSearchInput , &QLineEdit::textChanged, this, &MainWindow::searchForText);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _editorSearch;
}

void MainWindow::slSetInputFileNameVisible()
{
    ui->pbFileName->setVisible(true);
    ui->inputFileName->setVisible(true);
}

void MainWindow::slInputFileNameRead()
{
    QString s = ui->inputFileName->text();
    ui->inputFileName->setText(QString{});
    ui->inputFileName->setVisible(false);
    ui->pbFileName->setVisible(false);
    emit siInputFileNameProccesed(s);
}

void MainWindow::searchForText()
{
    QString searchString = ui->leSearchInput->text();

    emit searchButtonClicked(searchString, ui->htmlEditor->document());
}

