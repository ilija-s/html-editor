TEMPLATE = app
QT += gui

CONFIG += c++11

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="$${PWD}/../libs"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

INCLUDEPATH *= "$${PWD}/../../src"

HEADERS += $${PWD}/../../src/editorsettings/*.h

SOURCES +=     main.cpp\
    tst_editorsettings.cpp\
    $${PWD}/../../src/editorsettings/*.cpp



