#ifndef LINEDATA_H
#define LINEDATA_H

#include <QString>
#include <string>

class LineData {
public:
  LineData() = default;

  QString filename;
  int lineNumber{-1};
  QString content;
};

#endif // LINEDATA_H
