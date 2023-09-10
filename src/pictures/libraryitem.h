#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QFileInfo>
#include <QObject>
#include <QPixmap>

class LibraryItem : public QObject {
  Q_OBJECT
public:
  explicit LibraryItem(const QFileInfo &fileInfo, const QPixmap &pixmap, QObject *parent = nullptr);

  QFileInfo getImageFileInfo() const;
  QString getImageFilePath();
  QString getImageFileName();
  qint64 getImageFilesize();
  QSize getImageResolution();
  QByteArray getImageFormat();

  QPixmap pixmap() const;

  private:
  QFileInfo m_imageFileInfo;
  QPixmap m_pixmap;
};

#endif // LIBRARYITEM_H
