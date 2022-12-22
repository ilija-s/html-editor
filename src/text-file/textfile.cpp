#include "textfile.h"

#include <QFile>

TextFile::TextFile() {}

std::string TextFile::content() {
  if (m_content.empty()) {
    auto file = QFile(m_filename);
    if (!file.open(QFile::ReadOnly)) {
      m_content = file.readAll().toStdString();
    }
  }
  return m_content;
}

QVector<LineData> TextFile::find(const std::string &needle) {
  content();
  int currentLine = 0;
  int startOfLine = 0;
  QVector<LineData> matches;

  for (int i = 0; i < m_content.size(); ++i) {
    char ch = m_content.at(i);
    if (ch == '\n') {
      ++currentLine;
      std::string currentLineContent =
          m_content.substr(startOfLine, i - startOfLine);
      startOfLine += i + 1;
      if (currentLineContent.find(needle) != std::string::npos) {
        matches.push_back(LineData{m_filename, currentLine,
                                   QString(currentLineContent.data())});
      }
      continue;
    }
  }
  return matches;
}
