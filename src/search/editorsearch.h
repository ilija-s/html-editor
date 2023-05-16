#ifndef EDITORSEARCH_H
#define EDITORSEARCH_H

#include <QTextDocument>
#include <QWidget>

class EditorSearch : public QWidget
{
  Q_OBJECT

public:
  EditorSearch(QWidget* parent = nullptr);

public slots:
  void onSearchButtonClicked(const QString& searchString, QTextDocument* document);

private:
};

#endif // EDITORSEARCH_H
