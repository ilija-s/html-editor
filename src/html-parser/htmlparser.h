#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QVariantList>

class HTMLParser
{
public:
    HTMLParser() = default;
    QVariantList getMessages();
    void loadJsonData(std::string document);
    ~HTMLParser() = default;

private:
    QVariantList m_messages;
};

#endif // HTMLPARSER_H
