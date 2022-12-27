#include <catch2/catch.hpp>
#include <QString>
#include <QVector>
#include <QSharedPointer>
#include "../../src/syntaxhighlighting/tokenizer.h"
#include "../../src/syntaxhighlighting/tagparser.h"

TEST_CASE("HTML parsing", "[parsing]")
{

    SECTION("Tag parser parses opening tag with tag name only")
    {
        // Arrange
        QString input1 {"<html>"};
        QString input2 {"<h3>"};
        TagParser parser1 = TagParser(input1);
        TagParser parser2 = TagParser(input2);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();
        QSharedPointer<QVector<Token>> tokens2 = parser2.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 4),
                Token(TokenType::tag_close_bracket, 5, 1)
            }
        );

        REQUIRE(
            *tokens2 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 2),
                Token(TokenType::tag_close_bracket, 3, 1)
            }
        );
    }

    SECTION("Tag parser parses closing tag with tag name only")
    {
        // Arrange
        QString input1 {"</div>"};
        QString input2 {"</h6>"};
        TagParser parser1 = TagParser(input1);
        TagParser parser2 = TagParser(input2);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();
        QSharedPointer<QVector<Token>> tokens2 = parser2.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 2),
                Token(TokenType::tag_name, 2, 3),
                Token(TokenType::tag_close_bracket, 5, 1)
            }
        );

        REQUIRE(
            *tokens2 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 2),
                Token(TokenType::tag_name, 2, 2),
                Token(TokenType::tag_close_bracket, 4, 1)
            }
        );
    }

    SECTION("Tag parser parses autoclosing tag with tag name only")
    {
        // Arrange
        QString input1 {"<img/>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 3),
                Token(TokenType::tag_close_bracket, 4, 2)
            }
        );
    }

    SECTION("Tag parser parses attributes without assigned value")
    {
        // Arrange
        QString input1 {"<!DOCTYPE html>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 2),
                Token(TokenType::tag_name, 2, 7),
                Token(TokenType::attribute_name, 10, 4),
                Token(TokenType::tag_close_bracket, 14, 1)
            }
        );
    }

    SECTION("Tag parser parses attributes without assigned value")
    {
        // Arrange
        QString input1 {"<!DOCTYPE html>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 2),
                Token(TokenType::tag_name, 2, 7),
                Token(TokenType::attribute_name, 10, 4),
                Token(TokenType::tag_close_bracket, 14, 1)
            }
        );
    }

    SECTION("Tag parser parses attributes with assigned value")
    {
        // Arrange
        QString input1 {"<img href=\"img\"/>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 3),
                Token(TokenType::attribute_name, 5, 4),
                Token(TokenType::equals, 9, 1),
                Token(TokenType::attribute_value, 10, 5),
                Token(TokenType::tag_close_bracket, 15, 2)
            }
        );
    }

    SECTION("Tag parser parses multiple attributes")
    {
        // Arrange
        QString input1 {"<img href=\"img\" alt=\"img\"/>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 3),
                Token(TokenType::attribute_name, 5, 4),
                Token(TokenType::equals, 9, 1),
                Token(TokenType::attribute_value, 10, 5),
                Token(TokenType::attribute_name, 16, 3),
                Token(TokenType::equals, 19, 1),
                Token(TokenType::attribute_value, 20, 5),
                Token(TokenType::tag_close_bracket, 25, 2)
            }
        );
    }

    SECTION("Tag parser parses opening and closing bracket with code in between")
    {
        // Arrange
        QString input1 {"<a href=\"link\">Link</a>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 1),
                Token(TokenType::attribute_name, 3, 4),
                Token(TokenType::equals, 7, 1),
                Token(TokenType::attribute_value, 8, 6),
                Token(TokenType::tag_close_bracket, 14, 1),
                Token(TokenType::tag_open_bracket, 19, 2),
                Token(TokenType::tag_name, 21, 1),
                Token(TokenType::tag_close_bracket, 22, 1)
            }
        );
    }

    SECTION("Tag parser parses nested tags")
    {
        // Arrange
        QString input1 {"<div>\n\t<p>Test</p>\n</div>"};
        TagParser parser1 = TagParser(input1);

        // Act
        QSharedPointer<QVector<Token>> tokens1 = parser1.parse();

        // Assert
        REQUIRE(
            *tokens1 ==
            QVector<Token> {
                Token(TokenType::tag_open_bracket, 0, 1),
                Token(TokenType::tag_name, 1, 3),
                Token(TokenType::tag_close_bracket, 4, 1),
                Token(TokenType::tag_open_bracket, 7, 1),
                Token(TokenType::tag_name, 8, 1),
                Token(TokenType::tag_close_bracket, 9, 1),
                Token(TokenType::tag_open_bracket, 14, 2),
                Token(TokenType::tag_name, 16, 1),
                Token(TokenType::tag_close_bracket, 17, 1),
                Token(TokenType::tag_open_bracket, 19, 2),
                Token(TokenType::tag_name, 21, 3),
                Token(TokenType::tag_close_bracket, 24, 1)
            }
        );
    }


}
