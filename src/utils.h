#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

class Utils {
public:
  Utils();
  static QString toCamelCase(const QString &s);
  static QString getWritableDataPath(QStandardPaths::StandardLocation location,
                                     const QString &pathname);
  static QSize getSizeWithAspectRatio(int height, float aspectRatio);
};

#endif // UTILS_H
