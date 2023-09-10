#include "utils.h"

Utils::Utils() {}

QString Utils::toCamelCase(const QString &s) {
  QStringList parts = s.split(' ', Qt::SkipEmptyParts);
  for (int i = 0; i < parts.size(); ++i)
    parts[i].replace(0, 1, parts[i][0].toUpper());

  return parts.join(" ");
}

QString Utils::getWritableDataPath(QStandardPaths::StandardLocation location,
                                   const QString &pathname) {
  QString _data_path = QStandardPaths::writableLocation(location);
  QString path = _data_path + QDir::separator() + pathname + QDir::separator();
  QDir dir(path);
  if (!dir.exists()) {
    if (!dir.mkpath(path)) {
      qWarning() << "Failed to create directory:" << path;
    }
  }
  return path;
}

/**
 * Returns the size of a rectangle with the given height and aspect ratio.
 * The width is calculated to maintain the aspect ratio.
 *
 * @param height The height of the rectangle.
 * @param aspectRatio The aspect ratio of the rectangle (width/height).
 * @return The size of the rectangle.
 */
QSize Utils::getSizeWithAspectRatio(int height, float aspectRatio) {
  int width = qRound(height * aspectRatio);
  return QSize(width, height);
}
