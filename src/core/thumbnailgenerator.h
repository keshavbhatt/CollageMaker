#ifndef THUMBNAILGENERATOR_H
#define THUMBNAILGENERATOR_H

#include <QObject>
#include <QPixmap>

class ThumbnailGenerator : public QObject {
  Q_OBJECT
public:
  explicit ThumbnailGenerator(QObject *parent = nullptr);

public slots:
  void processImages(const QStringList &imagePaths);
  void setThumbnailSize(const QSize &size);

signals:
  void thumbnailGenerated(const QPixmap &thumbnail, const QString &imagePath);
  void finished();

  private slots:
  void cleanupBeforeQuit();
  private:
  QPixmap generateThumbnail(const QString &imagePath);
  QSize m_thumbnailSize;
};

#endif // THUMBNAILGENERATOR_H
