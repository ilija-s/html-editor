#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
#include <QString>
#include <QDir>

#include <src/text-file/textfile.h>

class Project
{
public:
    Project();
    void loadFileContents(QString directoryPath);
    std::vector<TextFile> fileContents();

private:
    std::vector<TextFile> m_fileContents;
};

#endif // PROJECT_H
