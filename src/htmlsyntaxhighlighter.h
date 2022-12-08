#ifndef HTMLSYNTAXHIGHLIGHTER_H
#define HTMLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class HtmlSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    HtmlSyntaxHighlighter(QTextDocument* document);
    void highlightBlock(const QString &text);
};

#endif // HTMLSYNTAXHIGHLIGHTER_H
