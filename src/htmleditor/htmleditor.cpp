#include "htmleditor.h"
#include <QFileDialog>

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

void HtmlEditor::NewFile() {

    this->html_file.setFileName(QString{});
    this->setPlainText(QString{});
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

void HtmlEditor::slNewFileMenuBar() {
    this->NewFile();
}

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
