#ifndef PROJECT_H
#define PROJECT_H

#include <src/text-file/textfile.h>

#include <QDir>
#include <QString>
#include <vector>

class Project {
   public:
    Project();
    void loadFileContents(QString directoryPath);
    void deleteFileContents();
    [[nodiscard]] auto textFiles() const -> std::vector<TextFile>;

private:
    std::vector<TextFile> m_textfiles;
};

#endif  // PROJECT_H
