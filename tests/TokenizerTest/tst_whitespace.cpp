#include <catch2/catch.hpp>
#include <QString>
#include "syntaxhighlighting/tokenizer.h"

TEST_CASE("Tokenizer skips all whitspace", "[tokenizer]")
{
    SECTION("Tokenizer skip spaces before a token")
    {
        // Arrange
        QString input1 {"    token"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 4, 5)
        );
    }

    SECTION("Tokenizer skips tabs before a token")
    {
        // Arrange
        QString input1 {"\t\ttoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 2, 5)
        );
    }

    SECTION("Tokenizer skips new lines before a token")
    {
        // Arrange
        QString input1 {"\n\ntoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 2, 5)
        );
    }
    SECTION("Tokenizer skip spaces after a token")
    {
        // Arrange
        QString input1 {"    token"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 4, 5)
        );
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer skips tabs after a token")
    {
        // Arrange
        QString input1 {"\t\ttoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 2, 5)
        );
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer skips new lines after a token")
    {
        // Arrange
        QString input1 {"\n\ntoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1 = tokenizer1.next();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(
            result1 ==
            Token(TokenType::tag_or_attribute_name, 2, 5)
        );
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer skips spaces between tokens")
    {
        // Arrange
        QString input1 {"token    token"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1_token1 = tokenizer1.next();
        Token result1_token2 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1_token1 ==
            Token(TokenType::tag_or_attribute_name, 0, 5)
        );
        REQUIRE(
            result1_token2 ==
            Token(TokenType::tag_or_attribute_name, 9, 5)
        );
    }

    SECTION("Tokenizer skips tabs between tokens")
    {
        // Arrange
        QString input1 {"token\t\t\t\ttoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1_token1 = tokenizer1.next();
        Token result1_token2 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1_token1 ==
            Token(TokenType::tag_or_attribute_name, 0, 5)
        );
        REQUIRE(
            result1_token2 ==
            Token(TokenType::tag_or_attribute_name, 9, 5)
        );
    }

    SECTION("Tokenizer skips new lines between tokens")
    {
        // Arrange
        QString input1 {"token\n\n\n\ntoken"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        Token result1_token1 = tokenizer1.next();
        Token result1_token2 = tokenizer1.next();

        // Assert
        REQUIRE(
            result1_token1 ==
            Token(TokenType::tag_or_attribute_name, 0, 5)
        );
        REQUIRE(
            result1_token2 ==
            Token(TokenType::tag_or_attribute_name, 9, 5)
        );
    }
}
