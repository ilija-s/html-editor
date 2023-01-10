#define CATCH_CONFIG_RUNNER
#include "./libs/catch2/catch.hpp"
#include <QtGui/QGuiApplication>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    return Catch::Session().run(argc, argv);
}
