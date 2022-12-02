#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbFileName->setVisible(false);
    ui->inputFileName->setVisible(false);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    /*
     * TODO:
     * do code refactoring so that trigger on open_file signals it to MainWindow::slSetInputFileNameVisible
     * which sets pbFileName and inputFileName to visible so that user can insert file name
     * Then when user presses ok, MainWindow::slInputFileNameRead will read from line edit and send file name inf
     * to HtmlEditor::slOpenFileMenuBar
     *
     *
     * connect(ui->actionOpen_file, &QAction::trigerred, this, &MainWindow::slSetInputFileNameVisible);
     * connect(ui->pbFileName, &QAbstractButton::clicked, this, &MainWindow::slInputFileNameRead);
     * connect(this, &MainWindow::siInputFileNameProccesed, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}
