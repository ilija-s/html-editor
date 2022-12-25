#include "htmlsyntaxhighlighter.h"
#include "tagparser.h"

#include <QSharedPointer>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>


HtmlSyntaxHighlighter::HtmlSyntaxHighlighter(QTextDocument* document):
    QSyntaxHighlighter(document)
{
    m_bracket_format.setForeground(QColor(171, 178, 191));
    m_tag_name_format.setForeground(QColor(97, 175, 239));
    m_attribute_name_format.setForeground(QColor(86, 182, 194));
    m_attribute_value_format.setForeground(QColor(229, 192, 123));

}

void HtmlSyntaxHighlighter::highlightBlock(const QString &text)
{
    TagParser tag_parser(text);

    QSharedPointer<QVector<Token>> tokens = tag_parser.parse();
    if(tokens) {
        for (const Token t : *tokens) {

            if (t.type() == TokenType::tag_open_bracket
                || t.type() == TokenType::tag_close_bracket) {

                setFormat(t.start(), t.length(), m_bracket_format);
            }
            else if (t.type() == TokenType::tag_name) {
                setFormat(t.start(), t.length(), m_tag_name_format);
            }
            else if (t.type() == TokenType::attribute_name) {
                setFormat(t.start(), t.length(), m_attribute_name_format);
            }
            else if (t.type() == TokenType::attribute_value) {
                setFormat(t.start(), t.length(), m_attribute_value_format);
            }
        }
    }
}
