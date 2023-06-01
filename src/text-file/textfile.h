#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <src/line-data/linedata.h>

#include <QString>
#include <string>

class TextFile {
   public:
    TextFile(QString filename, QString absoluteFilePath);
    QString filename() const;
    QString absoluteFilePath() const;
    std::string content();
    QVector<LineData> find(const std::string &needle);

   private:
    // This should really be QTextDocument
    std::string m_content;
    QString m_filename;
    QString m_absoluteFilePath;
};

#endif  // TEXTFILE_H
