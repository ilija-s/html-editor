#ifndef HTMLSYNTAXHIGHLIGHTER_H
#define HTMLSYNTAXHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

class HtmlSyntaxHighlighter : public QSyntaxHighlighter
{
public:
  HtmlSyntaxHighlighter(QTextDocument* document = nullptr);

protected:
  void highlightBlock(const QString& text);

private:
  QTextCharFormat m_bracket_format;
  QTextCharFormat m_tag_name_format;
  QTextCharFormat m_attribute_name_format;
  QTextCharFormat m_attribute_value_format;
  QTextCharFormat m_comment_format;
  QTextCharFormat m_blank_format;
};

#endif // HTMLSYNTAXHIGHLIGHTER_H
