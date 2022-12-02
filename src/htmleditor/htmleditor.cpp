#include "htmleditor.h"
#include <QFileDialog>

HtmlEditor::HtmlEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    file_name(QString{})
{

}

HtmlEditor::HtmlEditor()
{

}

HtmlEditor::~HtmlEditor()
{
}

void HtmlEditor::SaveFile(){

    if (this->html_file.exists()) {

        this->html_file.open(QIODevice::WriteOnly);

        QString content = this->toPlainText();
        QTextStream out(&this->html_file);

        out << content;

        this->html_file.close();
    }
    else {
        this->SaveAsFile();
    }

}

void HtmlEditor::SaveAsFile() {

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
    dialog.setMimeTypeFilters({"text/html"});

    if(dialog.exec()) {

        this->html_file.setFileName(dialog.selectedFiles()[0]);

        this->html_file.open(QIODevice::WriteOnly);

        QString content = this->toPlainText();
        QTextStream out(&this->html_file);

        out << content;

        this->html_file.close();
    }

}

void HtmlEditor::OpenFile() {

    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    dialog.setFileMode(QFileDialog::FileMode::ExistingFile);
    dialog.setMimeTypeFilters({"text/html"});

    if(dialog.exec()) {

        QString file_name = dialog.selectedFiles()[0];

        this->html_file.setFileName(file_name);
        this->html_file.open(QIODevice::ReadOnly);

        QTextStream in(&this->html_file);
        QString file_content;

        file_content = in.readAll();

        this->setPlainText(file_content);

        /*
         * TODO:
         * Set cursor to point behind the last character.
        */

        this->html_file.close();
    }
}

/*
 * TODO:
 * Add HtmlEditor::slNewFileMenuBar()
 * Add HtmlEditor::slSaveAsMenuBar()
*/

void HtmlEditor::slOpenFileMenuBar()
{
    this->OpenFile();
}

void HtmlEditor::slSaveFileMenuBar()
{
    this->SaveFile();
}

void HtmlEditor::slSaveAsFileMenuBar()
{
    this->SaveAsFile();
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
