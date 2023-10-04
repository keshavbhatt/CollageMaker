#include "imageutils.h"

QPixmap ImageUtils::blurPixmap(const QPixmap &inputPixmap, qreal blurRadius,
                               const QColor &fillColor) {

  QGraphicsScene scene;
  QGraphicsPixmapItem inputItem(inputPixmap);
  scene.addItem(&inputItem);

  QGraphicsBlurEffect blurEffect;
  blurEffect.setBlurHints(QGraphicsBlurEffect::PerformanceHint);
  blurEffect.setBlurRadius(blurRadius);

  inputItem.setGraphicsEffect(&blurEffect);

  QPixmap blurredPixmap(inputPixmap.size());

  blurredPixmap.fill(fillColor);

  QPainter painter(&blurredPixmap);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
  scene.render(&painter);

  return blurredPixmap;
}

QColor ImageUtils::getDominantColor(const QImage &img) {
  QRgb *ct;
  int width, height;
  width = img.width();
  height = img.height();

  QVector<int> red(256);
  QVector<int> green(256);
  QVector<int> blue(256);

  // Count the occurrence of each color component
  for (int i = 0; i < height; i++) {
    ct = (QRgb *)img.scanLine(i);
    for (int j = 0; j < width; j++) {
      red[qRed(ct[j])]++;
      green[qGreen(ct[j])]++;
      blue[qBlue(ct[j])]++;
    }
  }

  return QColor(get_max(red), get_max(green), get_max(blue));
}

int ImageUtils::get_max(const QVector<int> &values) {
  int max_val = 0;
  int max_idx = 0;

  for (int i = 0; i < values.size(); i++) {
    if (values[i] > max_val) {
      max_val = values[i];
      max_idx = i;
    }
  }

  return max_idx;
}

ImageUtils::ImageUtils() {}
