#include "project.h"

#include <QFileInfo>
#include <QFileInfoList>

Project::Project() = default;

void
Project::loadFileContents(QString directoryPath)
{
  QDir directory(directoryPath);
  QFileInfoList files =
    directory.entryInfoList(QStringList() << "*.html"
                                          << "*.css",
                            QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
  for (const auto& fileinfo : files) {
    TextFile textfile(fileinfo.fileName(), fileinfo.absoluteFilePath());
    m_textfiles.push_back(textfile);
  }
  QFileInfoList directoryInfoList =
    directory.entryInfoList(QStringList("*"),
                            QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                            QDir::Name | QDir::IgnoreCase);
  for (const auto& directoryInfo : directoryInfoList) {
    loadFileContents(directoryInfo.absoluteFilePath());
  }
}

void
Project::deleteFileContents()
{
  m_textfiles.clear();
}

auto
Project::textFiles() const -> std::vector<TextFile>
{
  return m_textfiles;
}
