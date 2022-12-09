#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbFileName->setVisible(false);
    ui->inputFileName->setVisible(false);
    ui->fontSize->setVisible(false);

    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::slSetInputFileNameVisible);
    connect(ui->pbFileName, &QAbstractButton::clicked, this, &MainWindow::slInputFileNameRead);
    connect(this, &MainWindow::siInputFileNameProccesed, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionFont_size, &QAction::triggered, this, &MainWindow::slFontSizeEnter);
    connect(ui->pbfontSize, &QAbstractButton::clicked, this, &MainWindow::slFontSizeChange);

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


