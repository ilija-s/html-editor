#include "htmlparser.h"

#include <cstdlib>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
#include <QVariantMap>
#include <QCoreApplication>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>

static void saveStringToFile(const std::string& str, const std::string& filepath)
{
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << str;
        file.close();
    }
}

static void callHtml5validatorAndSaveOutput(const std::string& fullpathJson, const std::string& fullpathHtml)
{
    std::string command = "html5validator --format json files " + fullpathHtml + " > " + fullpathJson;
    std::system(command.c_str());
}

// Reads data from a file and stores data in a list of maps
void HTMLParser::loadJsonData(std::string document)
{
    std::string applicationDirPath = QCoreApplication::applicationDirPath().toStdString();
    std::string fullpathHtml = applicationDirPath + "/data.html";
    std::string fullpathJson = applicationDirPath + "/data.json";
    saveStringToFile(document, fullpathHtml);
    callHtml5validatorAndSaveOutput(fullpathJson, fullpathHtml);

    QFile file{ QString::fromStdString(fullpathJson) };
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Json file couldn't be opened/found.";
        return;
    }

    QByteArray byteArray;
    byteArray = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(byteArray, &parseError);
    if(parseError.error != QJsonParseError::NoError){
        qWarning() << "Parse error at " << parseError.offset << ":" << parseError.errorString();
        return;
    }

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();
    QVariantMap json = jsonObj.toVariantMap();
    m_messages = json["messages"].toList();
}

QVariantList HTMLParser::getMessages()
{
    return m_messages;
}
