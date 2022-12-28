TEMPLATE = app
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}

SOURCES += \
    src/editorsettings/editorsettings.cpp \
    src/filetreeview/filetreeview.cpp \
    src/html-parser/htmlparser.cpp \
    src/htmleditor/htmleditor.cpp \
    src/line-data/linedata.cpp \
    src/project/project.cpp \
    src/search/editorsearch.cpp \
    src/main.cpp \
    src/numbersidebar/numbersidebar.cpp \
    src/mainwindow.cpp \
    src/syntaxhighlighting/htmlsyntaxhighlighter.cpp \
    src/syntaxhighlighting/tagparser.cpp \
    src/syntaxhighlighting/tokenizer.cpp \
    src/text-file/textfile.cpp \

HEADERS += \
    src/editorsettings/editorsettings.h \
    src/filetreeview/filetreeview.h \
    src/html-parser/htmlparser.h \
    src/htmleditor/htmleditor.h \
    src/line-data/linedata.h \
    src/project/project.h \
    src/search/editorsearch.h \
    src/numbersidebar/numbersidebar.h \
    src/mainwindow.h \
    src/syntaxhighlighting/htmlsyntaxhighlighter.h \
    src/syntaxhighlighting/tagparser.h \
    src/syntaxhighlighting/tokenizer.h \
    src/text-file/textfile.h

FORMS += \
    src/editorsettings/editorsettings.ui \
    form/mainwindow.ui

SOURCES += \
    tests/main.cpp \
    tests/text-file/textfile.test.cpp
