#ifndef IMAGEWIDGETITEM_H
#define IMAGEWIDGETITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include <QObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class CustomPixmapItem : public QGraphicsPixmapItem {
public:
  CustomPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
      : QGraphicsPixmapItem(pixmap, parent) {}

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override {

    // clip the rendering to the bounding rectangle of the item's parent (the
    // QGraphicsWidget)
    QRectF clipRect =
        parentItem() ? parentItem()->boundingRect() : boundingRect();
    painter->setClipRect(clipRect);

    QGraphicsPixmapItem::paint(painter, option, widget);
  }
};

class ImageWidgetItem : public QGraphicsWidget {
  Q_OBJECT
public:
  ImageWidgetItem(const QString &imageFilePath, const QSize &pixmapSize,
                  const QColor &borderColor = Qt::white,
                  qreal borderWidth = 0.0);

  qreal borderWidth() const;

  void setBorderColor(const QColor &newBorderColor);

  void setBorderWidth(qreal newBorderWidth);

  QColor borderColor() const;

  void reload();

  void setDesiredShadowEffectOffsetX(qreal newDesiredShadowEffectOffsetX);

  void setDesiredShadowEffectOffsetY(qreal newDesiredShadowEffectOffsetY);

  void setDesiredShadowEffectBlurRadius(qreal newDesiredShadowEffectBlurRadius);

  void setDesiredShadowEffectColor(const QColor &newDesiredShadowEffectColor);

  void toggleShadowEffect(bool turnOn);

  QPainterPath shape() const;

protected:
  QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

  QVariant itemChange(GraphicsItemChange change,
                      const QVariant &value) override;

private:
  CustomPixmapItem *m_pixmapItem;

  // pixmap
  QSizeF m_previousRectSize;
  QString m_imageFilePath;
  QPixmap m_pixmap;

  // borders
  QColor m_borderColor;
  qreal m_borderWidth;

  // shadow
  qreal m_desiredShadowEffectOffsetX = 0.0;
  qreal m_desiredShadowEffectOffsetY = 0.0;
  qreal m_desiredShadowEffectBlurRadius = 0;
  QColor m_desiredShadowEffectColor = QColor(63, 63, 63, 180);

  void updateShadowEffect();

};

#endif // IMAGEWIDGETITEM_H
