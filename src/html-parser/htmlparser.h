#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QVariantList>

class HTMLParser {
   public:
    HTMLParser(std::string document);
    QVariantList getMessages();
    ~HTMLParser() = default;

   private:
    QVariantList m_messages;
};

#endif  // HTMLPARSER_H
