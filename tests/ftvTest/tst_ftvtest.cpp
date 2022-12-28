#include "catch2/catch.hpp"

#include <filetreeview/filetreeview.h>

#include <QApplication>
#include <QWidget>
#include <QSignalSpy>

TEST_CASE("Test FileTreeView constructor", "[filetreeview]")
{
    //Arrange
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget* parent = nullptr;

    //Act
    FileTreeView treeView(parent);


    //Assert: Verify that the model has been set up correctly
    REQUIRE(treeView.getModel() != nullptr);
    REQUIRE(treeView.getModel()->rootPath() == QDir::currentPath());
    REQUIRE(treeView.rootIndex() == treeView.getModel()->index(QDir::currentPath()));

    //Assert: Verify that the header is hidden and all columns except the first are hidden
    REQUIRE(treeView.isHeaderHidden());
    REQUIRE(treeView.isColumnHidden(1));
    REQUIRE(treeView.isColumnHidden(2));
    REQUIRE(treeView.isColumnHidden(3));
    REQUIRE(!treeView.isColumnHidden(0));
}

TEST_CASE("Test FileTreeView SetFolder function, opening folder in tree view", "[filetreeview]")
{
    //Arrange
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget* parent = nullptr;
    FileTreeView treeView(parent);

    //Act
    treeView.SetFolder("/home/milos/Desktop");

    //Assert
    // Verify that the root path and root index have been set correctly
    REQUIRE(treeView.getModel()->rootPath() == "/home/milos/Desktop");
    REQUIRE(treeView.rootIndex() == treeView.getModel()->index("/home/milos/Desktop"));

    // Verify that the tree view is now visible
    REQUIRE(treeView.isVisible());
}

TEST_CASE("FileTreeView::slDoubleClicked", "[filetreeview]") {
    //Arrange
    int argc = 0;
    QApplication a{argc, nullptr};
    QWidget* parent = nullptr;
    FileTreeView treeView(parent);
    QSignalSpy spy(&treeView, &FileTreeView::siDoubleClicked);
    treeView.SetModel("/home/milos/Desktop");
    QModelIndex folderIndex = treeView.getModel()->index("/home/milos/Desktop");
    QModelIndex fileIndex = treeView.getModel()->index("/home/milos/Desktop/asd.html");

    //Act
    treeView.slDoubleClicked(folderIndex);
    //Assert
    REQUIRE(spy.count() == 0);
    //Act
    treeView.slDoubleClicked(fileIndex);
    //Assert
    REQUIRE(spy.count() == 1);
    REQUIRE(spy.at(0).at(0).toString() == "/home/milos/Desktop/asd.html");
}

