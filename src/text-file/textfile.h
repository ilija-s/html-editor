#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <src/line-data/linedata.h>

#include <QString>
#include <string>

class TextFile {
   public:
    TextFile(QString filename, QString absoluteFilePath);
    [[nodiscard]] auto filename() const -> QString;
    [[nodiscard]] auto absoluteFilePath() const -> QString;
    auto content() -> std::string;
    auto find(const std::string &needle) -> QVector<LineData>;

private:
    // This should really be QTextDocument
    std::string m_content;
    QString m_filename;
    QString m_absoluteFilePath;
};

#endif  // TEXTFILE_H
