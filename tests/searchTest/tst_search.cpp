#include <catch2/catch.hpp>
#include "../../src/search/editorsearch.h"

#include <QApplication>
#include <QTextCursor>
#include <QTextCharFormat>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    SECTION("Search for word that appears just once"){
        int argc = 0;
        QApplication a{argc, nullptr};
        QWidget *parent = nullptr;
        EditorSearch editorSearch1(parent);

        QTextDocument document;
        document.setPlainText("This is a test document with some test words.");
        QString word = "document";

        editorSearch1.onSearchButtonClicked(word, &document);

        QTextCursor cursor(&document);
        cursor.movePosition(QTextCursor::Start);
        cursor = document.find(word, cursor, QTextDocument::FindWholeWords);
        REQUIRE(cursor.charFormat().background().color() == Qt::yellow);
        REQUIRE(cursor.charFormat().foreground().color() == Qt::black);

    }

    SECTION("Found words are highlighted"){
        int argc = 0;
        QApplication a{argc, nullptr};
        QWidget *parent = nullptr;
        EditorSearch editorSearch1(parent);

        QTextDocument document;
        document.setPlainText("This is a test document with some test words.");
        QString word = "test";

        editorSearch1.onSearchButtonClicked(word, &document);

        QTextCursor cursor(&document);
        cursor.movePosition(QTextCursor::Start);
        int count = 0;
        while (!cursor.isNull() && !cursor.atEnd()) {
            cursor = document.find(word, cursor, QTextDocument::FindWholeWords);
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

    SECTION("Highlights are reset - first word for search is not highlighted anymore and the second one is highlighted"){

      int argc = 0;
      QApplication a{argc, nullptr};
      QWidget *parent = nullptr;
      EditorSearch editorSearch1(parent);

      QTextDocument document;
      document.setPlainText("This is a test document with some test words.");
      QString word = "test";

      //First search
      editorSearch1.onSearchButtonClicked(word, &document);

      //Second search
      word = "words";
      editorSearch1.onSearchButtonClicked(word, &document);

      QTextCursor cursor(&document);
      cursor.movePosition(QTextCursor::Start);
      int count = 0;
      while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = document.find(word, cursor, QTextDocument::FindWholeWords);
        if (!cursor.isNull()) {
          count++;
          QTextCharFormat format = cursor.charFormat();
          REQUIRE(format.background().color() == Qt::yellow);
          REQUIRE(format.foreground().color() == Qt::black);
        }
      }

      //We have 2 'test' and 1 'words', so if count is 2 or 3 then the old search is not reset
      REQUIRE(count == 1);
    }

    SECTION("Search for word that does not exists"){
        int argc = 0;
        QApplication a{argc, nullptr};
        QWidget *parent = nullptr;
        EditorSearch editorSearch1(parent);

        QTextDocument document;
        document.setPlainText("This is a test document with some test words.");
        QString word = "potato";

        editorSearch1.onSearchButtonClicked(word, &document);

        QTextCursor cursor(&document);
        cursor.movePosition(QTextCursor::Start);
        REQUIRE(cursor.isNull() == true);

        while (!cursor.isNull() && !cursor.atEnd()) {
            cursor.movePosition(QTextCursor::Right,
                                         QTextCursor::MoveAnchor, 1);
            QTextCharFormat format = cursor.charFormat();
            REQUIRE(format.background().color() == Qt::yellow);
            REQUIRE(format.foreground().color() == Qt::black);
          }
    }
}
