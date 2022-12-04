#include "editorsearch.h"
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QUiLoader>


static QWidget *loadUiFile(QWidget *parent)
{
    QFile file(":/form/mainwindow.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    return loader.load(&file, parent);
}

EditorSearch::EditorSearch(QWidget *parent)
    : QWidget(parent)
{
    QWidget *formWidget = loadUiFile(this);

    findButton = findChild<QPushButton*>("pbFind");
    text = findChild<HtmlEditor*>("htmlEditor");
    lineEdit = findChild<QLineEdit*>("leFindInput");

    QMetaObject::connectSlotsByName(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);

    setWindowTitle(tr("Text Finder"));
}

void EditorSearch::on_pbFind_clicked()
{
    QString searchString = lineEdit->text();
    QTextDocument *document = text->document();

    bool found = false;

    // undo previous change (if any)
    document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Empty Search Field"),
                                 tr("The search field is empty. "
                                    "Please enter a word and click Find."));
    } else {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setBackground(Qt::yellow);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor,
                                             QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                             QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();

        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                                     tr("Sorry, the word cannot be found."));
        }
    }
}
