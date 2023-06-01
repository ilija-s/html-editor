#include "filetreeview.h"

FileTreeView::FileTreeView(QWidget *parent) : QTreeView(parent) {
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    this->setModel(model);
    this->setRootIndex(model->index(QDir::currentPath()));
    this->setHeaderHidden(true);
    for (int i = 1; i < model->columnCount(); ++i) this->hideColumn(i);
    this->setVisible(false);
}

QFileSystemModel *FileTreeView::getModel() { return model; }

void FileTreeView::SetFolder(QString path) {
    SetModel(path);
    this->setVisible(true);
}

void FileTreeView::SetModel(QString path) {
    QFileInfo fi(path);
    if (!fi.isDir()) path = fi.dir().absolutePath();
    model->setRootPath(path);
    this->setRootIndex(model->index(path));
}

void FileTreeView::slDoubleClicked(const QModelIndex &index) {
    if (!model->fileInfo(index).isDir()) {
        QString path = model->filePath(index);
        emit siDoubleClicked(path);
    }
}
