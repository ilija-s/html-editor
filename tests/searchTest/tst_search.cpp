#include <catch2/catch.hpp>
#include "../../src/search/editorsearch.h"

#include <QApplication>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget *parent = nullptr;
    EditorSearch editorSearch1(parent);
    REQUIRE(0 == 0);
}
