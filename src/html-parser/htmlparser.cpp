#include "htmlparser.h"

#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QVariantMap>

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>


void HTMLParser::loadJsonData()
{
//    std::ifstream myFile("data.json");
//    std::ostringstream tmp;
//    tmp << myFile.rdbuf();
//    std::string jsonRawData = tmp.str();

//    QByteArray byteArray(jsonRawData.c_str(), jsonRawData.length());
    QJsonParseError parseError;

    QFile file;
    file.setFileName("data.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Json filef couldn't be opened/found";
        return;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();
    QVariantMap json = jsonObj.toVariantMap();
    auto pi = json["pi"];

//    QJsonValue pi;
//    pi = jsonObj.value("pi");

}
