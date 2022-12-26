#include "tokenizer.h"

#include <QString>
#include <QDebug>

/* Token */

TokenType Token::type() const{
    return m_type;
}

int Token::start() const{
    return m_start;
}

int Token::length() const{
    return m_length;
}

/* Tokenizer */

Token Tokenizer::next() {

    m_offset += whitespace_offset();

    if (m_offset >= m_text.size()) {
        m_current_token = Token(TokenType::eof, 0, 0);
        return m_current_token;
    }

    m_current_token = Token(TokenType::no_match, 0, 0);

    for (QPair<QRegularExpression, TokenType> token_regex : m_token_regular_expressions) {

        auto match = token_regex.first.match(m_text, m_offset);
        if (match.hasMatch() && match.capturedStart() == m_offset) {

            Token next_token = Token (
                token_regex.second,
                m_offset,
                match.capturedLength()
            );
            m_offset += next_token.length();

            m_current_token = next_token;
            break;
        }
    }


    return m_current_token;
}

Token Tokenizer::peek() {
    return m_current_token;
}

int Tokenizer::whitespace_offset() {

    auto whitespace_match = m_white_space_re.match(m_text, m_offset);

    if (whitespace_match.hasMatch() && whitespace_match.capturedStart() == m_offset) {
        return whitespace_match.capturedLength();
    }
    else {
        return 0;
    }
}
