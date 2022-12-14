#include "htmleditor.h"
#include <QFileDialog>
#include <string>
#include <QPainter>
#include <QTextBlock>
HtmlEditor::HtmlEditor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    connect(this, &HtmlEditor::blockCountChanged, this, &HtmlEditor::UpdateNumberBarWidth);
    connect(this, &HtmlEditor::updateRequest, this, &HtmlEditor::UpdateNumberBar);


}

HtmlEditor::~HtmlEditor()
{

}

void HtmlEditor::SetNumberSideBar(NumberSideBar *sb)
{
    number_bar = sb;
    UpdateNumberBarWidth();
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

void HtmlEditor::slNumberBarPaintEvent(QPaintEvent *event)
{
    QPainter painter(number_bar);
    painter.fillRect(event->rect(), QPlainTextEdit::palette(). color(QPlainTextEdit::backgroundRole()));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = this->y();
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::lightGray);
            painter.drawText(0, top, number_bar->width, fontMetrics().height(),
                             Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int HtmlEditor::NumberBarWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 9 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void HtmlEditor::UpdateNumberBarWidth()
{
    number_bar->width = NumberBarWidth();
    setViewportMargins(number_bar->width, 0, 0, 0);
}

void HtmlEditor::UpdateNumberBar(const QRect &rect, int dy)
{
    if (dy)
        number_bar->scroll(0, dy);
    else
        number_bar->update(0, rect.y(), number_bar->width, rect.height());

    if (rect.contains(viewport()->rect()))
        UpdateNumberBarWidth();
}

void HtmlEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    number_bar->width = NumberBarWidth();
    number_bar->setGeometry(QRect(cr.left(), cr.top(), number_bar->width, cr.height()));
}

void HtmlEditor::fontSizeChange(int mainSize)
{
     this->size = mainSize;

     QFont font = QFont();
     font.setPointSize(size);
     this->setFont(font);

}
