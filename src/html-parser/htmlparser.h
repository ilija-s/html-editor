#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QJsonObject>

class HTMLParser
{
public:
    HTMLParser() = default;
    void loadJsonData();

private:
    QJsonObject m_data;
};

#endif // HTMLPARSER_H
