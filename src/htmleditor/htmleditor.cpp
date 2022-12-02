#include "htmleditor.h"

HtmlEditor::HtmlEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{

}

HtmlEditor::HtmlEditor()
{

}

HtmlEditor::~HtmlEditor()
{
}

void HtmlEditor::SaveFile(){
    /*
     * TODO:
     * store file name as private field which will be set on first save (a.k.a save as)
    */
    this->html_file.setFileName("Untitled.html");
    this->html_file.open(QIODevice::ReadWrite | QIODevice::Truncate);

    QString content = this->toPlainText();
    QTextStream out(&this->html_file);
    out << content;

    this->html_file.close();
}

/*
 * TODO:
 * Add HtmlEditor::slNewFileMenuBar()
 * Add HtmlEditor::slSaveAsMenuBar()
*/

void HtmlEditor::slSaveFileMenuBar()
{
    this->SaveFile();
}

void HtmlEditor::slOpenFileMenuBar()
{
    /*
     * TODO:
     * get file name from MainWindow::siInputFileNameProcessed
     * instead of hard coding
    */
    this->html_file.setFileName("Untitled.html");
    this->html_file.open(QIODevice::ReadOnly);

    QTextStream in(&this->html_file);
    QString file_content;
    QString line;
    while(in.readLineInto(&line)){
        file_content.push_back(line);
    }
    this->setPlainText(file_content);

    /*
     * TODO:
     * Set cursor to point behind the last character.
    */

    this->html_file.close();

}

void HtmlEditor::keyPressEvent(QKeyEvent *event)
{
    if((event->modifiers() & Qt::ControlModifier) && (event->key() == Qt::Key_S)){
        //TODO: Handle "save" and "save as" separately
        this->SaveFile();
    }else{
        QPlainTextEdit::keyPressEvent(event);
    }
}
