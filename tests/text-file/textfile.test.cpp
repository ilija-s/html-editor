#include "../src/text-file/textfile.h"
#include "tests/libs/catch2/catch.hpp"
#include <QFile>

TEST_CASE("Test the constructor of TextFile", "[TextFile]")
{
    SECTION("Test that filename and absoluteFilePath are set correctly.")
    {
        // Arrange
        // Act
        TextFile file("test.txt", "/path/to/test.txt");
        // Assert
        REQUIRE(file.filename() == "test.txt");
        REQUIRE(file.absoluteFilePath() == "/path/to/test.txt");
    }

    SECTION("Test that the content is empty.")
    {
        // Arrange
        // Act
        TextFile file("test.txt", "/path/to/test.txt");
        // Assert
        REQUIRE(file.content() == "");
    }
}

TEST_CASE("Test the content function of TextFile") {
  TextFile file("test.txt", "./test.txt");

  // Set up a mock file with known content
  QFile mockFile("./test.txt");
  mockFile.open(QIODevice::WriteOnly);
  mockFile.write("Hello, world!\nThis is a test file.\n");
  mockFile.close();

  REQUIRE(file.content() == "Hello, world!\nThis is a test file.\n");
}

TEST_CASE("Test the find function of TextFile") {
  TextFile file("test.txt", "./test.txt");

  // Set up a mock file with known content
  QFile mockFile("./test.txt");
  mockFile.open(QIODevice::WriteOnly);
  mockFile.write("Hello, world!\nThis is a test file.\n");
  mockFile.close();

  QVector<LineData> matches = file.find("test");
  REQUIRE(matches.size() == 1);
  REQUIRE(matches[0].filename == "test.txt");
  REQUIRE(matches[0].absoluteFilePath == "./test.txt");
  REQUIRE(matches[0].lineNumber == 2);
  REQUIRE(matches[0].content == "This is a test file.");
}
