TEMPLATE = app
QT += gui widgets testlib

CONFIG += c++11

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="$${PWD}/../libs"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

INCLUDEPATH *= "$${PWD}/../../src"

HEADERS += \
    $${PWD}/../../src/filetreeview/*.h


SOURCES += \
    main.cpp \
    tst_ftvtest.cpp \
    $${PWD}/../../src/filetreeview/*.cpp
