QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    src/text-file/textfile.cpp

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

RESOURCES = form/mainwindow.ui \
            resources/res.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data.json
