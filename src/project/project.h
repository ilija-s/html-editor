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
    void deleteFileContents();
    std::vector<TextFile> textFiles() const;

private:
    std::vector<TextFile> m_textfiles;
};

#endif // PROJECT_H
