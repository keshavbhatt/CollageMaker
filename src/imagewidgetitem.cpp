#include "imagewidgetitem.h"
#include <QDebug>

ImageWidgetItem::ImageWidgetItem(const QPixmap &pixmap,
                                 const QColor &borderColor, qreal borderWidth)
    : QGraphicsWidget(), m_borderColor(borderColor),
      m_borderWidth(borderWidth) {
  m_pixmapItem = new CustomPixmapItem(pixmap, this);
}

QSizeF ImageWidgetItem::sizeHint(Qt::SizeHint which,
                                 const QSizeF &constraint) const {
  switch (which) {
  case Qt::MinimumSize:
  case Qt::PreferredSize:
  case Qt::MaximumSize:
    return m_pixmapItem->boundingRect().size();
  default:
    return constraint;
  }
}

qreal ImageWidgetItem::borderWidth() const { return m_borderWidth; }

void ImageWidgetItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {

  QGraphicsWidget::paint(painter, option, widget);

  if (m_borderWidth > 0.0) {
    // draw a border around the widget
    QPen pen;
    pen.setColor(m_borderColor);
    pen.setWidthF(m_borderWidth);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(
        Qt::NoBrush); // no brush required for the border, we draw only outline
    painter->drawRect(boundingRect().adjusted(
        0.0, 0.0, 0.0, 0.0)); // adjust the rectangle to stay inside the bounds
  }
}
