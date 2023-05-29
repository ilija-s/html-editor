#include "mainwindow.h"

#include <QApplication>

/*
 * So far the application has simple input field to write our html code.
 * You can save file on ctrl+s and also from menu bar. Document is not saved before this.
 * You can open file from menu bar.
 * Save as not implemented yet, if you are saving your document for the first time,
 * default file name is Untitled.html
 */

auto
main(int argc, char* argv[]) -> int
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
