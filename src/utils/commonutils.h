#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QtCore>

class CommonUtils {
public:
  static QSize getSizeWithAspectRatio(int height, float aspectRatio);

  static QString getWritableDataPath(QStandardPaths::StandardLocation location,
                                     const QString &pathname);
  static QString toCamelCase(const QString &s);

  static qreal sliderValueToReal(qreal minValue, qreal maxValue,
                                 qreal sliderMaximum, qreal sliderValue);

private:
  CommonUtils();
};

#endif // COMMONUTILS_H
