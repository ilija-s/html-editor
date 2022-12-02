#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbFileName->setVisible(false);
    ui->inputFileName->setVisible(false);

    connect(ui->pbFileName, &QAbstractButton::clicked, this, &MainWindow::slInputFileNameRead);
    connect(this, &MainWindow::siInputFileNameProccesed, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);

    // Menu bar signals
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionSave_file_as, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveAsFileMenuBar);

}

MainWindow::~MainWindow()
{
    delete ui;
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
