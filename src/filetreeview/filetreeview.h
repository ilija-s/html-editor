#ifndef FILETREEVIEW_H
#define FILETREEVIEW_H

#include <QFileInfo>
#include <QFileSystemModel>
#include <QObject>
#include <QWidget>
#include <iostream>
#include <qtreeview.h>

class FileTreeView : public QTreeView
{
  Q_OBJECT
public:
  FileTreeView(QWidget* parent = nullptr);
  ~FileTreeView(){};
  QFileSystemModel* getModel();
public slots:
  void SetFolder(QString path);
  void SetModel(QString path);
  void slDoubleClicked(const QModelIndex& index);

signals:
  void siDoubleClicked(const QString& path);

private:
  QFileSystemModel* model;
};

#endif // FILETREEVIEW_H
