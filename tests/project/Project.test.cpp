#include "src/project/project.h"

#include <QFile>
#include <vector>

#include "src/text-file/textfile.h"
#include "tests/libs/catch2/catch.hpp"

TEST_CASE("Test loadFileContents method", "[Project]") {
    SECTION(
        "When given a valid directory path containing HTML file, project contains one text file.") {
        // Arrange
        Project project;
        // Set up a mock file with known content
        QFile mockFile("./test.html");
        mockFile.open(QIODevice::WriteOnly);
        mockFile.write("<h1>Content</h1>");
        mockFile.close();

        // Act
        // Test with a valid directory path containing HTML and CSS files
        QString directoryPath = "../";
        project.loadFileContents(directoryPath);
        std::vector<TextFile> textFiles = project.textFiles();

        // Assert
        REQUIRE(textFiles.size() == 1);
        REQUIRE(textFiles[0].filename() == "test.html");
    }

    SECTION("When given an invalid directory path, project contains no text files.") {
        // Arrange
        Project project;

        // Act
        // Test with an invalid directory path
        QString directoryPath = "/path/to/invalid/directory";
        project.loadFileContents(directoryPath);
        std::vector<TextFile> textFiles = project.textFiles();

        // Assert
        REQUIRE(textFiles.empty());
    }
}

TEST_CASE("Test deleteFileContents method", "[Project]") {
    SECTION(
        "When the deleteFileContents is called on project that contains text files, deletes all of "
        "the text files.") {
        // Arrange
        Project project;

        // Act
        QString directoryPath = "../";
        project.loadFileContents(directoryPath);
        std::vector<TextFile> textFiles = project.textFiles();
        // Assert that textFiles is not empty
        REQUIRE(textFiles.size() > 0);
        // Then delete the file contents
        project.deleteFileContents();
        textFiles = project.textFiles();

        // Assert
        REQUIRE(textFiles.empty());
    }
}

TEST_CASE("Test textFiles method", "[Project]") {
    // Arrange
    Project project;
    QFile mockFile("./test2.html");
    mockFile.open(QIODevice::WriteOnly);
    mockFile.write("<h1>Test 2 content</h1>");
    mockFile.close();

    // Act
    // Load some file contents first
    QString directoryPath = "/path/to/valid/directory";
    project.loadFileContents(directoryPath);
    std::vector<TextFile> textFiles = project.textFiles();

    // Assert
    REQUIRE(textFiles.size() == 2);

    // Check if the returned textFiles are the same as the ones loaded
    std::vector<TextFile> expectedTextFiles = {TextFile("test.html", "./test.html"),
                                               TextFile("test2.html", "./test2.html")};
    REQUIRE(textFiles[0].filename() == expectedTextFiles[0].filename());
    REQUIRE(textFiles[0].absoluteFilePath() == expectedTextFiles[0].absoluteFilePath());
    REQUIRE(textFiles[1].filename() == expectedTextFiles[1].filename());
    REQUIRE(textFiles[1].absoluteFilePath() == expectedTextFiles[1].absoluteFilePath());
}
