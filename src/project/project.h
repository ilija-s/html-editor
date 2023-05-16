#ifndef PROJECT_H
#define PROJECT_H

#include <QDir>
#include <QString>
#include <vector>

#include <src/text-file/textfile.h>

class Project
{
public:
  Project();
  void loadFileContents(QString directoryPath);
  void deleteFileContents();
  std::vector<TextFile> textFiles() const;

private:
  std::vector<TextFile> m_textfiles;
};

#endif // PROJECT_H
