#ifndef IMAGEWIDGETITEM_H
#define IMAGEWIDGETITEM_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class ImageWidgetItem : public QGraphicsItem {

public:
  ImageWidgetItem(const QString &imageFilePath, const QRectF &pixmapSize,
                  const QColor &borderColor = Qt::white,
                  qreal borderWidth = 0.0);

  QRectF boundingRect() const override;

  void setBorderColor(const QColor &newBorderColor);

  void setBorderWidth(qreal newBorderWidth);

  void reload(QRectF newRectF);

  void setDesiredShadowEffectOffsetX(qreal newDesiredShadowEffectOffsetX);

  void setDesiredShadowEffectOffsetY(qreal newDesiredShadowEffectOffsetY);

  void setDesiredShadowEffectBlurRadius(qreal newDesiredShadowEffectBlurRadius);

  void setDesiredShadowEffectColor(const QColor &newDesiredShadowEffectColor);

  void toggleShadowEffect(bool turnOn);

  void setDesiredBorderCornerSize(qreal newDesiredBorderCornerSize);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

private:
  // pixmap
  QRectF m_previousRectF;
  QString m_imageFilePath;
  QPixmap m_pixmap;

  // borders
  QColor m_desiredBorderColor;
  qreal m_desiredBorderWidth;

  // corner
  qreal m_desiredBorderCornerSize = 0.0;

  // shadow
  qreal m_desiredShadowEffectOffsetX = 0.0;
  qreal m_desiredShadowEffectOffsetY = 0.0;
  qreal m_desiredShadowEffectBlurRadius = 0.0;
  QColor m_desiredShadowEffectColor = QColor(63, 63, 63, 180);

  void updateShadowEffect();

  QPixmap getCenterPixelRegion(const QPixmap &originalPixmap,
                               const QSizeF requestedSize);

  QPixmap getCenterPixelRegionIntPrecesion(const QPixmap &originalPixmap,
                                           const QSizeF size);

  QPixmap getCenterPixelRegionExact(const QPixmap &originalPixmap,
                                    const QSizeF size);
};

#endif // IMAGEWIDGETITEM_H
