#include "editorsearch.h"

#include <QPlainTextEdit>

EditorSearch::EditorSearch(QWidget *parent) : QWidget(parent) {}

void EditorSearch::onSearchButtonClicked(const QString &searchString, QTextDocument *document) {
    // Used for resetting all the highlights from the previous search
    document->setPlainText(document->toPlainText());

    QTextCursor highlightCursor(document);
    QTextCursor cursor(document);
    QTextCharFormat plainFormat(highlightCursor.charFormat());
    QTextCharFormat colorFormat = plainFormat;

    cursor.beginEditBlock();

    colorFormat.setBackground(Qt::yellow);
    colorFormat.setForeground(Qt::black);

    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
        highlightCursor =
            document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

        if (!highlightCursor.isNull()) {
            highlightCursor.movePosition(QTextCursor::NoMove, QTextCursor::KeepAnchor);
            highlightCursor.mergeCharFormat(colorFormat);
        }
    }

    cursor.endEditBlock();
}
