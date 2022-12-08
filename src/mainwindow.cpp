#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->htmlEditor->SetNumberSideBar(ui->numberSideBar);
    // Menu bar signals
    connect(ui->actionNew_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slNewFileMenuBar);
    connect(ui->actionOpen_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slOpenFileMenuBar);
    connect(ui->actionSave_file, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveFileMenuBar);
    connect(ui->actionSave_file_as, &QAction::triggered, ui->htmlEditor, &HtmlEditor::slSaveAsFileMenuBar);
    connect(ui->numberSideBar, &NumberSideBar::siPaintEvent, ui->htmlEditor, &HtmlEditor::slNumberBarPaintEvent);

    // Menu bar shortcuts
    ui->actionNew_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    ui->actionOpen_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    ui->actionSave_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    ui->actionSave_file_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
}

MainWindow::~MainWindow()
{
    delete ui;
}
