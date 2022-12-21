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

    parse_tags();

    return m_tokens;
}

void TagParser::parse_tags() {

    Token lookahead;

    do {
        lookahead = m_tokenizer.next();
    } while (lookahead.type() != TokenType::tag_open_bracket
             && lookahead.type() != TokenType::eof);

    if (lookahead.type() == TokenType::eof) {
        return;
    }

    m_tokens->push_back(lookahead);
}


