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
  ImageWidgetItem(const QPixmap &pixmap, const QColor &borderColor,
                  qreal borderWidth = 0.0);

  qreal borderWidth() const;

protected:
  QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

private:
  CustomPixmapItem *m_pixmapItem;

  QColor m_borderColor;
  qreal m_borderWidth;
};

#endif // IMAGEWIDGETITEM_H
