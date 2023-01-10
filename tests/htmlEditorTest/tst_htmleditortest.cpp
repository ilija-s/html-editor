#include "catch2/catch.hpp"
#include <src/htmleditor/htmleditor.h>
#include <QApplication>
#include <QPlainTextEdit>
#include <QPainter>

TEST_CASE("Test HtmlEditor SetNumberSideBar function", "[htmleditor]")
{
    // Arrange
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget* parent = nullptr;
    HtmlEditor* editor = new HtmlEditor(parent);
    NumberSideBar* sb = new NumberSideBar(parent);

    // Act
    editor->SetNumberSideBar(sb);


    // Assert
    // Verify that the number_bar field is set correctly
    REQUIRE(editor->getNumberBar() == sb);

    // Verify that the unit_width field of the NumberSideBar object is set correctly
    REQUIRE(sb->unit_width == 9 + editor->fontMetrics().horizontalAdvance(QLatin1Char('9')));
}


