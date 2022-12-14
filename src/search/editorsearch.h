#ifndef EDITORSEARCH_H
#define EDITORSEARCH_H

#include <QWidget>
#include <QTextDocument>

class EditorSearch : public QWidget
{
    Q_OBJECT

public:
    EditorSearch(QWidget *parent = nullptr);

public slots:
    void onSearchButtonClicked(const QString& searchString, QTextDocument *document);

private:
};

#endif // EDITORSEARCH_H
