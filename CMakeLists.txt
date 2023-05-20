cmake_minimum_required(VERSION 3.10)
project(HtmlEditor VERSION 1.0.0)

set(CMAKE_PREFIX_PATH "/home/nata/Qt/6.4.3/gcc_64")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)

set(RESOURCES ${RESOURCES} resources/res.qrc)
set(RESOURCES ${RESOURCES} resources/error.png)
set(RESOURCES ${RESOURCES} resources/warning.png)

qt6_add_resources(RES_SOURCES ${RESOURCES})

set(SOURCES
    "src/editorsettings/editorsettings.cpp"
    "src/html-parser/htmlparser.cpp"
    "src/project/project.cpp"
    "src/text-file/textfile.cpp"
    "src/filetreeview/filetreeview.cpp"
    "src/line-data/linedata.cpp"
    "src/search/editorsearch.cpp"
    "src/htmleditor/htmleditor.cpp"
    "src/numbersidebar/numbersidebar.cpp"
    "src/syntaxhighlighting/htmlsyntaxhighlighter.cpp"
    "src/syntaxhighlighting/tagparser.cpp"
    "src/syntaxhighlighting/tokenizer.cpp"
    "src/main.cpp"
    "src/mainwindow.cpp"
)

set(HEADERS
    "src/editorsettings/editorsettings.h"
    "src/html-parser/htmlparser.h"
    "src/project/project.h"
    "src/text-file/textfile.h"
    "src/filetreeview/filetreeview.h"
    "src/line-data/linedata.h"
    "src/search/editorsearch.h"
    "src/htmleditor/htmleditor.h"
    "src/numbersidebar/numbersidebar.h"
    "src/syntaxhighlighting/htmlsyntaxhighlighter.h"
    "src/syntaxhighlighting/tagparser.h"
    "src/syntaxhighlighting/tokenizer.h"
    "src/mainwindow.h"
)

set(FORMS
    "form/mainwindow.ui"
    "src/editorsettings/editorsettings.ui"
)

qt6_wrap_ui(UI_HEADERS ${FORMS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RES_SOURCES} ${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt6::Gui Qt6::Widgets)
