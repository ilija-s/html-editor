#include "htmleditor.h"

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

void HtmlEditor::setSize(int s)
{
    this->size = s;
}

void HtmlEditor::SaveFile(){
    /*
     * TODO:
     * store file name as private field which will be set on first save (a.k.a save as)
    */
    if(this->file_name.length() == 0){
        this->file_name = "Untitled.html";
    }
    this->html_file.setFileName(this->file_name);
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


void HtmlEditor::slOpenFileMenuBar(const QString& name)
{
    this->html_file.setFileName(name);
    this->html_file.open(QIODevice::ReadOnly);
    this->file_name = name;

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

void HtmlEditor::slSaveFileMenuBar()
{
    this->SaveFile();
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

void HtmlEditor::fontSizeChange()
{
     QFont font = QFont();
     font.setPointSize(size);
     this->setFont(font);

}
