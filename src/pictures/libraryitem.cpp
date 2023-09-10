#include "libraryitem.h"

#include <QImageReader>

LibraryItem::LibraryItem(const QFileInfo &fileInfo, const QPixmap &pixmap,
                         QObject *parent)
    : QObject(parent), m_imageFileInfo(fileInfo), m_pixmap(pixmap) {}

QFileInfo LibraryItem::getImageFileInfo() const { return m_imageFileInfo; }

QString LibraryItem::getImageFileName() { return m_imageFileInfo.fileName(); }

qint64 LibraryItem::getImageFilesize() { return m_imageFileInfo.size(); }

QSize LibraryItem::getImageResolution() {
  QImageReader reader(getImageFilePath());
  return reader.size();
}

QByteArray LibraryItem::getImageFormat() {
  QImageReader reader(getImageFilePath());
  return reader.format();
}

QPixmap LibraryItem::pixmap() const
{
  return m_pixmap;
}

QString LibraryItem::getImageFilePath() { return m_imageFileInfo.filePath(); }
