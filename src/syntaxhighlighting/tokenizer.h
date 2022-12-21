#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QString>
#include <QRegularExpression>


enum TokenType
{
    tag_open_bracket,
    tag_close_bracket,
    tag_name,
    attribute_name,
    equals,
    attribute_value,
    none,
    no_match,
    eof
};

class Token
{
public:

    Token()
        :m_type(TokenType::none), m_start(0), m_length(0)
    {}

    Token(TokenType type, int start, int length)
        : m_type(type), m_start(start), m_length(length)
    {}

    TokenType type() const;
    int start() const;
    int length() const;

private:

    TokenType m_type;
    int m_start;
    int m_length;
};


class Tokenizer
{
public:

    Tokenizer(const QString& text)
        :m_text(text), m_offset(0)
    {}

    Token next();

private:

    int whitespace_offset();

    const QString& m_text;
    int m_offset;

    QRegularExpression m_tag_open_bracket_re {"<!|<\\/|<"};
    QRegularExpression m_tag_close_bracket_re {">|\\/>"};
    QRegularExpression m_tag_name_re {"[a-zA-Z0-9]+"};
    QRegularExpression m_attribute_name_re {"[a-zA-Z]+"};
    QRegularExpression m_equals_re {"="};
    QRegularExpression m_attribute_value_re {"[0-9]+|[\"][^\"]+[\"]"};
    QRegularExpression m_white_space_re {"\\s+"};
    QRegularExpression m_none_re {"."};
};

#endif // TOKENIZER_H
