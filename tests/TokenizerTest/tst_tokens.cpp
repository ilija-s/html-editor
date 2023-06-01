#include <QString>
#include <catch2/catch.hpp>

#include "syntaxhighlighting/tokenizer.h"

TEST_CASE("Tokenizer matches individual tokens", "[tokenizer][regex]") {
    SECTION("Tokenizer matches open tag bracket") {
        // Arrange
        QString input1{"<"};
        QString input2{"<!"};
        QString input3{"</"};
        Tokenizer tokenizer1 = Tokenizer(input1);
        Tokenizer tokenizer2 = Tokenizer(input2);
        Tokenizer tokenizer3 = Tokenizer(input3);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        TokenType result2_type = tokenizer2.next().type();
        TokenType result2_eof = tokenizer2.next().type();

        TokenType result3_type = tokenizer3.next().type();
        TokenType result3_eof = tokenizer3.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::tag_open_bracket);
        REQUIRE(result1_eof == TokenType::eof);

        REQUIRE(result2_type == TokenType::tag_open_bracket);
        REQUIRE(result2_eof == TokenType::eof);

        REQUIRE(result3_type == TokenType::tag_open_bracket);
        REQUIRE(result3_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches close tag brackets") {
        // Arrange
        QString input1{">"};
        QString input2{"/>"};
        Tokenizer tokenizer1 = Tokenizer(input1);
        Tokenizer tokenizer2 = Tokenizer(input2);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        TokenType result2_type = tokenizer2.next().type();
        TokenType result2_eof = tokenizer2.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::tag_close_bracket);
        REQUIRE(result1_eof == TokenType::eof);

        REQUIRE(result2_type == TokenType::tag_close_bracket);
        REQUIRE(result2_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches tag names and attribute names") {
        // Arrange
        QString input1{"h5"};
        QString input2{"style"};
        QString input3{"accept-charset"};
        Tokenizer tokenizer1 = Tokenizer(input1);
        Tokenizer tokenizer2 = Tokenizer(input2);
        Tokenizer tokenizer3 = Tokenizer(input3);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        TokenType result2_type = tokenizer2.next().type();
        TokenType result2_eof = tokenizer2.next().type();

        TokenType result3_type = tokenizer3.next().type();
        TokenType result3_eof = tokenizer3.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::tag_or_attribute_name);
        REQUIRE(result1_eof == TokenType::eof);

        REQUIRE(result2_type == TokenType::tag_or_attribute_name);
        REQUIRE(result2_eof == TokenType::eof);

        REQUIRE(result3_type == TokenType::tag_or_attribute_name);
        REQUIRE(result3_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches equals sign") {
        // Arrange
        QString input1{"="};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::equals);
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches attribute value") {
        // Arrange
        QString input1{"\"backgournd-color:green;\""};
        QString input2{"\"\""};
        Tokenizer tokenizer1 = Tokenizer(input1);
        Tokenizer tokenizer2 = Tokenizer(input2);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        TokenType result2_type = tokenizer2.next().type();
        TokenType result2_eof = tokenizer2.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::attribute_value);
        REQUIRE(result1_eof == TokenType::eof);

        REQUIRE(result2_type == TokenType::attribute_value);
        REQUIRE(result2_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches comment start") {
        // Arrange
        QString input1{"<!--"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::comment_start);
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches comment end") {
        // Arrange
        QString input1{"-->"};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::comment_end);
        REQUIRE(result1_eof == TokenType::eof);
    }

    SECTION("Tokenizer matches end of input") {
        // Arrange
        QString input1{""};
        Tokenizer tokenizer1 = Tokenizer(input1);

        // Act
        TokenType result1_type = tokenizer1.next().type();
        TokenType result1_eof = tokenizer1.next().type();

        // Assert
        REQUIRE(result1_type == TokenType::eof);
        REQUIRE(result1_eof == TokenType::eof);
    }
}
