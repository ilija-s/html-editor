#include "filetreeview.h"

FileTreeView::FileTreeView(QWidget* parent)
    : QTreeView(parent)
{
    setHidden(true);
}

FileTreeView::~FileTreeView()
{

}

void FileTreeView::SetModel(QString path)
{
    setVisible(true);
    QFileInfo fi(path);
    QString dir_name = fi.dir().absolutePath();
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(dir_name);
    this->setModel(model);
    this->setRootIndex(model->index(dir_name));
    this->setHeaderHidden(true);
    for (int i = 1; i < model->columnCount(); ++i)
        this->hideColumn(i);
}

void FileTreeView::slDoubleClicked(const QModelIndex &index)
{
    QString path = model->filePath(index);
    emit siDoubleClicked(path);
}

