TEMPLATE = app
QT += gui widgets testlib

CONFIG += c++11

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="$${PWD}/../libs"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

INCLUDEPATH *= "$${PWD}/../../"

HEADERS += \
    $${PWD}/../../src/htmleditor/*.h \
    $${PWD}/../../src/numbersidebar/*.h \
    $${PWD}/../../src/syntaxhighlighting/*.h

SOURCES += \
    main.cpp \
    tst_htmleditortest.cpp \
    $${PWD}/../../src/htmleditor/*.cpp \
    $${PWD}/../../src/numbersidebar/*.cpp \
    $${PWD}/../../src/syntaxhighlighting/*.cpp



