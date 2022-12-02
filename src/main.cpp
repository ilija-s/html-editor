#include "mainwindow.h"

#include <QApplication>

/*
 * So far the application has simple input field to write our html code.
 * You can save file on ctrl+s and also from menu bar. Document is not saved before this.
 * You can open file from menu bar.
 * Note that application always opens and saves file with name "Untitled.html" (will be changed soon)
 * PushButton and TextField for file name input (to be opened or saved or created)
 *  are added but so far invisible and useless (no logic implemented yet).
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
