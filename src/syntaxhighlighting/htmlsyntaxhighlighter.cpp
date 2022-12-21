#include "htmlsyntaxhighlighter.h"
#include "tagparser.h"

#include <QSharedPointer>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>


HtmlSyntaxHighlighter::HtmlSyntaxHighlighter(QTextDocument* document):
    QSyntaxHighlighter(document)
{
    tagNameExpression = QRegularExpression(QStringLiteral("(?<=[<])\\w+(?=((\\s)|([>])))"));
    tagNameFormat.setForeground(QColor(224, 108, 117));

    attributeNameExpression = QRegularExpression(QStringLiteral("(?<=[>]+)\\w+(?=\\s*[=])"));
    attributeNameFormat.setForeground(QColor(229, 192, 123));


}

void HtmlSyntaxHighlighter::highlightBlock(const QString &text)
{
    TagParser tag_parser(text);

    QSharedPointer<QVector<Token>> tokens = tag_parser.parse();
    if(tokens) {
        for (const Token t : *tokens) {
            setFormat(t.start(), t.length(), tagNameFormat);
        }
    }
}
