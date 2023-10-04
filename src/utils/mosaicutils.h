#ifndef MOSAICUTILS_H
#define MOSAICUTILS_H

#include <QList>
#include <QRandomGenerator>
#include <QRectF>

class MosaicUtils {
public:
  struct MosaicLayout {
    QList<QRectF> itemsRects;
  };

  static MosaicUtils::MosaicLayout generateMosaicLayout(int itemCount,
                                                        QSizeF sceneSize);

  static MosaicUtils::MosaicLayout
  generateMosaicLayout(int itemCount, QSizeF sceneSize, qreal spacing);

private:
  MosaicUtils();
};

#endif // MOSAICUTILS_H
