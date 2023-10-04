#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QtCore>

class ImageUtils {
public:
  static QPixmap blurPixmap(const QPixmap &inputPixmap, qreal blurRadius,
                            const QColor &fillColor);

  static QColor getDominantColor(const QImage &img);

private:
  ImageUtils();
  static int get_max(const QVector<int> &values);
};

#endif // IMAGEUTILS_H
