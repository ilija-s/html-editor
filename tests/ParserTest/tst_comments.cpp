#include <catch2/catch.hpp>
#include <QString>
#include <QVector>
#include <QSharedPointer>

#include "syntaxhighlighting/tokenizer.h"
#include "syntaxhighlighting/tagparser.h"

TEST_CASE("Parsing HTML comments", "[parsing]")
{
    SECTION("Tag parser comment opening")
    {
        // Arrange
        QString input1 {"Text Before <!-- Text After"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> result1 = parser1.parse();

        // Assert
        REQUIRE(
            *result1 ==
            QVector<Token> {
                Token(TokenType::comment_start, 12, 4)
            }
        );
    }

    SECTION("Tag parser comment closing")
    {
        // Arrange
        QString input1 {"Text Before --> Text After"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> result1 = parser1.parse();

        // Assert
        REQUIRE(
            *result1 ==
            QVector<Token> {
                Token(TokenType::comment_end, 12, 3)
            }
        );
    }

    SECTION("Tag parser parses HTML even when inside a comment")
    {
        // Arrange
        QString input1 {"<!--<img/>-->"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> result1 = parser1.parse();

        // Assert
        REQUIRE(
            *result1 ==
            QVector<Token> {
                Token(TokenType::comment_start, 0, 4),
                Token(TokenType::tag_open_bracket, 4, 1),
                Token(TokenType::tag_name, 5, 3),
                Token(TokenType::tag_close_bracket, 8, 2),
                Token(TokenType::comment_end, 10, 3)
            }
        );
    }
}
