#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QString>
#include <string>

#include <src/line-data/linedata.h>

class TextFile {
public:
  TextFile();
  std::string content();
  QVector<LineData> find(const std::string &needle);

private:
  // This should really be QTextDocument
  std::string m_content;
  QString m_filename;
};

#endif // TEXTFILE_H
