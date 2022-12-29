#include <catch2/catch.hpp>
#include "../../src/editorsettings/editorsettings.h"

#include <QApplication>
#include <QWidget>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    SECTION("Test fFontSize function") {
        int argc = 0;
        QApplication a{argc, nullptr};
        QWidget *parent = nullptr;
        EditorSettings editorSettings(parent);

        editorSettings.fFontSize();

        REQUIRE(editorSettings.getUi()->wInitial->isVisible() == false);
        REQUIRE(editorSettings.getUi()->wFontSize->isVisible() == true);
        REQUIRE(editorSettings.getUi()->cbSize->isEditable() == true);
        REQUIRE(editorSettings.getUi()->lNotValid->isVisible() == false);
    }
}
