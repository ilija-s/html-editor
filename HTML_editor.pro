QT       += core gui
QT       += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/htmleditor/htmleditor.cpp \
    src/search/editorsearch.cpp \
    src/main.cpp \
    src/numbersidebar/numbersidebar.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/htmleditor/htmleditor.h \
    src/search/editorsearch.h \
    src/numbersidebar/numbersidebar.h \
    src/mainwindow.h

FORMS += \
    form/mainwindow.ui

RESOURCES = form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
