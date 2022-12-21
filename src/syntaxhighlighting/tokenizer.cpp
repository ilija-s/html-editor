#include "tokenizer.h"

#include <QString>

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

    if (m_offset == m_text.size()) {
        return Token(TokenType::eof, 0, 0);
    }

    m_offset += whitespace_offset();

    if (m_offset == m_text.size()) {
        return Token(TokenType::eof, 0, 0);
    }

    auto open_bracket_match = m_tag_open_bracket_re.match(m_text, m_offset);
    if (open_bracket_match.hasMatch() && open_bracket_match.capturedStart() == 0) {

        Token next_token = Token(
            TokenType::tag_open_bracket,
            m_offset,
            open_bracket_match.capturedLength()
        );
        m_offset += next_token.length();

        return next_token;
    }

    auto none_match = m_none_re.match(m_text, m_offset);
    if (none_match.hasMatch() && none_match.capturedStart() == 0) {

        Token next_token = Token(
            TokenType::none,
            m_offset,
            none_match.capturedLength()
        );
        m_offset += next_token.length();

        return next_token;
    }

    return Token(TokenType::no_match, 0, 0);
}

int Tokenizer::whitespace_offset() {

    auto whitespace_match = m_white_space_re.match(m_text, m_offset);

    if (whitespace_match.hasMatch() && whitespace_match.capturedStart() == 0) {
        return whitespace_match.capturedLength();
    }
    else {
        return 0;
    }
}
