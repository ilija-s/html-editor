#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QVariantList>
#include <QList>
#include <QVariant>

class HTMLParser
{
public:
  HTMLParser(std::string document);
  QList<QVariant> getMessages();
  ~HTMLParser() = default;

private:
  QList<QVariant> m_messages;
};

#endif // HTMLPARSER_H
