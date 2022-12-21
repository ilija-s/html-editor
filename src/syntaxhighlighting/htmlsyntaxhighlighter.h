#ifndef HTMLSYNTAXHIGHLIGHTER_H
#define HTMLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class HtmlSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    HtmlSyntaxHighlighter(QTextDocument* document = nullptr);

protected:
    void highlightBlock(const QString &text);

private:

    QRegularExpression tagNameExpression;
    QRegularExpression attributeNameExpression;
    QRegularExpression atributeValueExpression;

    QTextCharFormat tagNameFormat;
    QTextCharFormat attributeNameFormat;
    QTextCharFormat attributeValueFormat;
};

#endif // HTMLSYNTAXHIGHLIGHTER_H
