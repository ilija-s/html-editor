#include "project.h"

#include <QFileInfoList>
#include <QFileInfo>

Project::Project()
{
}

void Project::loadFileContents(QString directoryPath)
{
    QDir directory(directoryPath);
    QFileInfoList files = directory.entryInfoList(QStringList() << "*.html" << "*.css",
                                                  QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    foreach (QFileInfo fileinfo, files) {
        TextFile textfile(fileinfo.fileName(), fileinfo.absoluteFilePath());
        m_textfiles.push_back(textfile);
    }
    QFileInfoList directoryInfoList = directory.entryInfoList(QStringList("*"),
                                                              QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                                                              QDir::Name | QDir::IgnoreCase );
    foreach (QFileInfo directoryInfo, directoryInfoList) {
        loadFileContents(directoryInfo.absoluteFilePath());
    }
}

void Project::deleteFileContents()
{
    m_textfiles.clear();
}

std::vector<TextFile> Project::textFiles()
{
    return m_textfiles;
}
