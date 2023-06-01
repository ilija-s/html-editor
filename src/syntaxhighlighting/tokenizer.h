#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QRegularExpression>
#include <QString>

enum TokenType {
    tag_open_bracket,
    tag_close_bracket,
    tag_name,
    attribute_name,
    tag_or_attribute_name,
    equals,
    attribute_value,
    comment_start,
    comment_end,
    none,
    no_match,
    eof
};

class Token {
   public:
    Token() : m_type(TokenType::no_match), m_start(0), m_length(0) {}

    Token(TokenType type, int start, int length) : m_type(type), m_start(start), m_length(length) {}

    TokenType type() const;
    int start() const;
    int length() const;

    bool operator==(const Token& other) const;

   private:
    TokenType m_type;
    int m_start;
    int m_length;
};

class Tokenizer {
   public:
    Tokenizer(const QString& text) : m_text(text), m_offset(0), m_current_token(Token()) {}

    Token next();
    Token peek();

   private:
    int whitespace_offset();

    const QString& m_text;
    int m_offset;
    Token m_current_token;

    QRegularExpression m_white_space_re{"\\s+"};

    QPair<QRegularExpression, TokenType> m_token_regular_expressions[8] = {
        QPair<QRegularExpression, TokenType>(QRegularExpression("<!--"), TokenType::comment_start),
        QPair<QRegularExpression, TokenType>(QRegularExpression("-->"), TokenType::comment_end),
        QPair<QRegularExpression, TokenType>(QRegularExpression("<!|<\\/|<"),
                                             TokenType::tag_open_bracket),
        QPair<QRegularExpression, TokenType>(QRegularExpression("[a-zA-Z0-9-]+"),
                                             TokenType::tag_or_attribute_name),
        QPair<QRegularExpression, TokenType>(QRegularExpression("="), TokenType::equals),
        QPair<QRegularExpression, TokenType>(QRegularExpression("[\"][^\"]*[\"]"),
                                             TokenType::attribute_value),
        QPair<QRegularExpression, TokenType>(QRegularExpression(">|\\/>"),
                                             TokenType::tag_close_bracket),

        QPair<QRegularExpression, TokenType>(QRegularExpression("."), TokenType::none)};
};

#endif  // TOKENIZER_H
