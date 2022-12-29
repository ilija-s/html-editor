#include <catch2/catch.hpp>
#include "../../src/search/editorsearch.h"

#include <QApplication>
#include <QTextCursor>
#include <QTextCharFormat>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget *parent = nullptr;
    EditorSearch editorSearch1(parent);


    QTextDocument document;
    document.setPlainText("This is a test document with some test words.");
    QString searchString = "test";

    editorSearch1.onSearchButtonClicked(searchString, &document);

    QTextCursor cursor(&document);
    cursor.movePosition(QTextCursor::Start);
    int count = 0;
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document.find(searchString, cursor, QTextDocument::FindWholeWords);
        if (!cursor.isNull()) {
          count++;
          QTextCharFormat format = cursor.charFormat();
          REQUIRE(format.background().color() == Qt::yellow);
          REQUIRE(format.foreground().color() == Qt::black);
        }
      }

    //The word appears 2 times
    REQUIRE(count == 2);
}
