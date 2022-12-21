#ifndef TAGPARSER_H
#define TAGPARSER_H

#include "tokenizer.h"

#include <QVector>
#include <QString>
#include <QSharedPointer>
#include <optional>


class TagParser
{
public:

    TagParser(const QString& text)
        : m_tokenizer(text)
    {};

    QSharedPointer<QVector<Token>> parse();

private:

    Tokenizer m_tokenizer;
    QSharedPointer<QVector<Token>> m_tokens;

    void parse_tags();
};

#endif // TAGPARSER_H
