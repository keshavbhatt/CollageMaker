#include "thumbnailgenerator.h"

#include <QCoreApplication>
#include <QDebug>
#include <QThread>

ThumbnailGenerator::ThumbnailGenerator(QObject *parent)
    : QObject{parent}, m_thumbnailSize(QSize(120, 120)) {
  connect(qApp, &QCoreApplication::aboutToQuit, this,
          &ThumbnailGenerator::cleanupBeforeQuit);
}

void ThumbnailGenerator::processImages(const QStringList &imagePaths) {
  foreach (const QString &imagePath, imagePaths) {

    if (QThread::currentThread()->isInterruptionRequested()) {
      emit finished();
      // Thread is interrupted; exit gracefully
      return;
    }

    QPixmap thumbnail = generateThumbnail(imagePath);

    if (!thumbnail.isNull()) {
      emit thumbnailGenerated(thumbnail, imagePath);
    }
  }
  emit finished();
}

void ThumbnailGenerator::cleanupBeforeQuit() {
  if (this->thread() && this->thread()->isRunning()) {
    // Stop the thread
    this->thread()
        ->requestInterruption(); // This signals the thread to exit gracefully

    // Wait for the thread to finish (optional but recommended)
    this->thread()->wait();
    emit finished();
  }
}

void ThumbnailGenerator::setThumbnailSize(const QSize &size) {
  m_thumbnailSize = size;
}

QPixmap ThumbnailGenerator::generateThumbnail(const QString &imagePath) {
  QPixmap original(imagePath);
  if (original.isNull()) {
    qWarning() << metaObject()->className() << ":"
               << "Failed to load image:" << imagePath;
    return QPixmap(); // Return an empty pixmap for failed images
  }

  QPixmap thumbnail = original.scaled(m_thumbnailSize, Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation);
  return thumbnail;
}
