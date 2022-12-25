#include "tagparser.h"
#include "tokenizer.h"

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include <QRegularExpression>

/*
Grammer:

Tag ->                      OpenTagBracket TagName AttributeList CloseTagBracket { OpenTagBracket }

AttributeList ->            Attribute AttributeList { AttributeName }
                            eps { CloseTagBracket }

Attribute ->                AttributeName AttributeDeclaration { AttributeName }

AttributeDeclaration ->     '=' AttributeValue { '=' }
                            eps { AttributeName CloseTagBracket }

Tag:
    First { OpenTagBracket }
    Follow { eoi }
AttributeList:
    First { AttributeName }
    Followe { CloseTagBracket }
Attribute:
    First {AttributeName }
    Follow { AttributeName CloseTagBracket }
AttributeDeclaratio:
    First { '=' }
    Follow { AttributeName CloseTagBracket }

*/

QSharedPointer<QVector<Token>> TagParser::parse() {

    m_tokens = QSharedPointer<QVector<Token>>(new QVector<Token>());

    if (parse_all_tags()) {
       return m_tokens;
    }
    else {
        return nullptr;
    }
}

bool TagParser::parse_all_tags() {

    Token lookahead;

    while (lookahead.type() != TokenType::eof) {

        do {
            lookahead = m_tokenizer.next();
        } while (lookahead.type() != TokenType::tag_open_bracket
                 && lookahead.type() != TokenType::eof);

        if (lookahead.type() == TokenType::eof) {
            continue;
        }

        bool parse_success = parse_tag();
        if (!parse_success) {
            return false;
        }
    }

    return true;
}

bool TagParser::parse_tag() {

    Token lookahead = m_tokenizer.peek();

    if (lookahead.type() == TokenType::tag_open_bracket) {

        m_tokens->push_back(lookahead);
        lookahead = m_tokenizer.next();

        if (lookahead.type() != TokenType::tag_or_attribute_name) {
            return false;
        }

        Token mod_token = Token(
            TokenType::tag_name,
            lookahead.start(),
            lookahead.length()
        );
        m_tokens->push_back(mod_token);
        lookahead = m_tokenizer.next();

        bool parse_success = parse_attribute_list();
        if (!parse_success) {
            return false;
        }

        lookahead = m_tokenizer.peek();

        if (lookahead.type() != TokenType::tag_close_bracket) {
            return false;
        }

        m_tokens->push_back(lookahead);
        lookahead = m_tokenizer.next();

        return true;
    }
    else {
        return false;
    }
}

bool TagParser::parse_attribute_list() {

    Token lookahead = m_tokenizer.peek();

    if (lookahead.type() == TokenType::tag_or_attribute_name) {

        bool parse_succes = parse_attribute();
        if (!parse_succes) {
            return false;
        }

        parse_succes = parse_attribute_list();
        if (!parse_succes) {
            return false;
        }

        return true;
    }
    else if (lookahead.type() == TokenType::tag_close_bracket) {
        return true;
    }
    else {
        return false;
    }
}

bool TagParser::parse_attribute() {

    Token lookahead = m_tokenizer.peek();

    if (lookahead.type() == TokenType::tag_or_attribute_name) {

        Token mod_token = Token(
            TokenType::attribute_name,
            lookahead.start(),
            lookahead.length()
        );
        m_tokens->push_back(mod_token);
        m_tokenizer.next();

        bool parse_succes = parse_attribute_declaration();
        if (!parse_succes) {
            return false;
        }

        return true;
    }
    else {
        return false;
    }
}

bool TagParser::parse_attribute_declaration() {

    Token lookahead = m_tokenizer.peek();

    if (lookahead.type() == TokenType::equals) {

        m_tokens->push_back(lookahead);
        lookahead = m_tokenizer.next();

        if (lookahead.type() != TokenType::attribute_value) {
            return false;
        }

        m_tokens->push_back(lookahead);
        lookahead = m_tokenizer.next();

        return true;

    }
    else if (lookahead.type() == TokenType::tag_or_attribute_name
             || lookahead.type() == TokenType::tag_close_bracket) {

        return true;
    }
    else {
        return false;
    }
}


