#include "textfile.h"

#include <QDebug>
#include <QFile>
#include <sstream>
#include <utility>

TextFile::TextFile(QString filename, QString absoluteFilePath)
    : m_filename(std::move(filename))
    , m_absoluteFilePath(std::move(absoluteFilePath))
{}

auto TextFile::filename() const -> QString
{
    return m_filename;
}

auto TextFile::absoluteFilePath() const -> QString
{
    return m_absoluteFilePath;
}

auto TextFile::content() -> std::string
{
    if (m_content.empty()) {
        auto file = QFile(m_absoluteFilePath);
        if (file.open(QFile::ReadOnly)) {
            m_content = file.readAll().toStdString();
        }
    }
    return m_content;
}

auto TextFile::find(const std::string &needle) -> QVector<LineData>
{
    content();

    int currentLine = 0;
    QVector<LineData> matches;
    std::istringstream content(m_content);
    std::string line;
    while (std::getline(content, line)) {
        ++currentLine;
        if (line.find(needle) != std::string::npos) {
            matches.push_back(
                LineData{m_filename, m_absoluteFilePath, currentLine, QString(line.c_str())});
        }
    }
    return matches;
}
