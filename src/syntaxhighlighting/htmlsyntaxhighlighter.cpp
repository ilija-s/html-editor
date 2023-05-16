#include "htmlsyntaxhighlighter.h"
#include "tagparser.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QSharedPointer>

HtmlSyntaxHighlighter::HtmlSyntaxHighlighter(QTextDocument* document)
    : QSyntaxHighlighter(document)
{
  m_bracket_format.setForeground(QColor(171, 178, 191));
  m_tag_name_format.setForeground(QColor(97, 175, 239));
  m_attribute_name_format.setForeground(QColor(86, 182, 194));
  m_attribute_value_format.setForeground(QColor(229, 192, 123));
  m_comment_format.setForeground(QColor(120, 195, 121));
  m_blank_format.setForeground(QColor(255, 255, 255));
}

void
HtmlSyntaxHighlighter::highlightBlock(const QString& text)
{
  TagParser tag_parser(text);
  bool inside_comment;

  if (previousBlockState() == 1) {
    inside_comment = true;
    setCurrentBlockState(1);
    setFormat(0, text.length(), m_comment_format);
  } else {
    setCurrentBlockState(0);
    inside_comment = false;
  }

  QSharedPointer<QVector<Token>> tokens = tag_parser.parse();
  if (tokens) {
    for (const Token t : *tokens) {

      if (t.type() == TokenType::comment_start) {
        inside_comment = true;
        setFormat(t.start(), text.length(), m_comment_format);
        setCurrentBlockState(1);
      } else if (t.type() == TokenType::comment_end) {
        inside_comment = false;
        setFormat(t.start() + t.length(), text.length(), m_blank_format);
        setCurrentBlockState(0);
      }

      if (!inside_comment) {

        if (t.type() == TokenType::tag_open_bracket ||
            t.type() == TokenType::tag_close_bracket) {

          setFormat(t.start(), t.length(), m_bracket_format);
        } else if (t.type() == TokenType::tag_name) {
          setFormat(t.start(), t.length(), m_tag_name_format);
        } else if (t.type() == TokenType::attribute_name) {
          setFormat(t.start(), t.length(), m_attribute_name_format);
        } else if (t.type() == TokenType::attribute_value) {
          setFormat(t.start(), t.length(), m_attribute_value_format);
        }
      }
    }
  }
}
