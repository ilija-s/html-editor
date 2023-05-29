#include "mainwindow.h"
#include "html-parser/htmlparser.h"
#include "ui_mainwindow.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _editorSearch(new EditorSearch(this))
{
  ui->setupUi(this);
  ui->htmlEditor->SetNumberSideBar(ui->numberSideBar);
  ui->htmlEditor->setTabStopDistance(
    QFontMetricsF(ui->htmlEditor->font()).horizontalAdvance(' ') * 2);

  // Shortcuts
  auto showOrHideFindInProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+F", "Find in project")), this);
  auto showOrHideMessagesShortcut = new QShortcut(QKeySequence(tr("Ctrl+M", "Open messages")), this);

  // Menu bar signals
  connect(ui->actionNew_file,
          &QAction::triggered,
          ui->htmlEditor,
          &HtmlEditor::slNewFileMenuBar);
  connect(ui->actionOpen_file,
          &QAction::triggered,
          ui->htmlEditor,
          &HtmlEditor::slOpenFileMenuBar);
  connect(ui->actionOpen_folder,
          &QAction::triggered,
          ui->htmlEditor,
          &HtmlEditor::slOpenFolderMenuBar);
  connect(ui->actionSave_file,
          &QAction::triggered,
          ui->htmlEditor,
          &HtmlEditor::slSaveFileMenuBar);
  connect(ui->htmlEditor,
          &HtmlEditor::siFileExists,
          this,
          &MainWindow::parseHtmlFileAndDisplayMessages);
  connect(ui->actionSave_file_as,
          &QAction::triggered,
          ui->htmlEditor,
          &HtmlEditor::slSaveAsFileMenuBar);
  connect(ui->numberSideBar,
          &NumberSideBar::siPaintEvent,
          ui->htmlEditor,
          &HtmlEditor::slNumberBarPaintEvent);
  connect(this,
          &MainWindow::searchButtonClicked,
          _editorSearch,
          &EditorSearch::onSearchButtonClicked);
  connect(ui->leSearchInput, &QLineEdit::textChanged, this, &MainWindow::searchForText);
  connect(ui->treeView,
          &FileTreeView::doubleClicked,
          ui->treeView,
          &FileTreeView::slDoubleClicked);
  connect(ui->treeView,
          &FileTreeView::siDoubleClicked,
          ui->htmlEditor,
          &HtmlEditor::slTreeViewDoubleClicked);
  connect(
    ui->htmlEditor, &HtmlEditor::siOpenFolder, ui->treeView, &FileTreeView::SetFolder);
  connect(
    ui->htmlEditor, &HtmlEditor::siOpenFolder, this, &MainWindow::updateProjectFolder);
  connect(
    ui->htmlEditor, &HtmlEditor::siFileSaved, this, &MainWindow::updateProjectFolder);
  connect(
    ui->htmlEditor, &HtmlEditor::siSetCursorAtLine, this, &MainWindow::setCursorAtLine);
  connect(
    ui->htmlEditor, &HtmlEditor::siFileExists, this, &MainWindow::updateWindowTitle);
  connect(ui->leFindInProjectSearchQuery,
          &QLineEdit::returnPressed,
          this,
          &MainWindow::findInProjectClicked);
  connect(
    ui->pbFindInProject, &QPushButton::clicked, this, &MainWindow::findInProjectClicked);
  connect(ui->lwLinesFound,
          &QListWidget::itemDoubleClicked,
          ui->htmlEditor,
          &HtmlEditor::slOpenFileAtLine);
  connect(showOrHideFindInProjectShortcut,
          &QShortcut::activated,
          this,
          &MainWindow::toggleShowOrHideFindInProjectTab);
  connect(showOrHideMessagesShortcut,
          &QShortcut::activated,
          this,
          &MainWindow::toggleShowOrHideMessagesTab);

  // Editor settings
  connect(ui->actionSettings_2,
          &QAction::triggered,
          this,
          &MainWindow::MainWindow::slEditorSettingsWindowOpen);

  // Menu bar shortcuts
  ui->actionNew_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
  ui->actionOpen_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
  ui->actionSave_file->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
  ui->actionSave_file_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

  ui->htmlEditor->setFocus();
}

MainWindow::~MainWindow()
{
  delete ui;
  delete _editorSearch;
}

void
MainWindow::updateWindowTitle(QString filename)
{
  if (filename.isEmpty()) {
    this->setWindowTitle("HtmlEditor");
  } else {
    QStringList tokens = filename.split("/");
    this->setWindowTitle(tokens[tokens.length() - 1] + " - HtmlEditor");
  }
}

void
MainWindow::searchForText()
{
  QString searchString = ui->leSearchInput->text();

  emit searchButtonClicked(searchString, ui->htmlEditor->document());
}

void
MainWindow::slEditorSettingsWindowOpen()
{
  editorSettingsWindow = new EditorSettings(this);
  editorSettingsWindow->show();

  connect(editorSettingsWindow,
          &EditorSettings::siFontSizeAccepted,
          this,
          &MainWindow::slFontSizeAccepted);
}

void
MainWindow::slFontSizeAccepted(int fontSize, int ind)
{
  if (ind) {
    ui->htmlEditor->fontSizeChange(fontSize);
  }
}

void
MainWindow::updateProjectFolder(QString projectDirPath)
{
  if (!projectDirPath.isEmpty()) {
    m_projectDirPath = projectDirPath;
  }
  m_project.deleteFileContents();
  m_project.loadFileContents(m_projectDirPath);
}

void
MainWindow::setCursorAtLine(int linenumber)
{
  ui->htmlEditor->setFocus();
  QTextCursor cursor = ui->htmlEditor->textCursor();
  cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, linenumber - 1);
  ui->htmlEditor->setTextCursor(cursor);
}

void
MainWindow::findInProjectClicked()
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
      QString text(data.filename + ": " + std::to_string(data.lineNumber).c_str() + "\t" +
                   content);
      auto* item = new QListWidgetItem(text);
      item->setWhatsThis(data.absoluteFilePath);
      ui->lwLinesFound->addItem(item);
    }
  }
}

void
MainWindow::parseHtmlFileAndDisplayMessages()
{
  // In the future this should underscore words that have errors

  // Clear all previous items
  ui->lwEditorMessages->clear();

  std::string textDocument = ui->htmlEditor->document()->toPlainText().toStdString();
  std::unique_ptr<HTMLParser> htmlParser = std::make_unique<HTMLParser>(textDocument);

  // Add items to QListWidget
  QList<QVariant> listOfMessages = htmlParser.get()->getMessages();
  // TODO: This looks really bad, extract to a method or try using std::transform
  for (auto & listOfMessage : listOfMessages) {
    QMap map = listOfMessage.toMap();
    QString type = map["type"].toString();
    QString message = map["message"].toString();
    QString lastLine = map["lastLine"].toString();
    QString text = "Line: " + lastLine + " Message: " + message;
    QIcon icon = QIcon(":/images/" + type + ".png");
    auto* item = new QListWidgetItem(icon, text);
    ui->lwEditorMessages->addItem(item);
  }
}

void
MainWindow::toggleShowOrHideFindInProjectTab()
{
  m_isBottomTabWidgetVisible = !m_isBottomTabWidgetVisible;
  if (m_isBottomTabWidgetVisible) {
    ui->tabWidget->setVisible(true);
    ui->searchTab->setFocus();
  } else {
    ui->tabWidget->setVisible(false);
  }
}

void
MainWindow::toggleShowOrHideMessagesTab()
{
  m_isBottomTabWidgetVisible = !m_isBottomTabWidgetVisible;
  if (m_isBottomTabWidgetVisible) {
    ui->tabWidget->setVisible(true);
    ui->messageTab->setFocus();
  } else {
    ui->tabWidget->setVisible(false);
  }
}
