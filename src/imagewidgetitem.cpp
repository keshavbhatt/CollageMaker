#include "imagewidgetitem.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGuiApplication>
#include <QScreen>

ImageWidgetItem::ImageWidgetItem(const QString &imageFilePath,
                                 const QSize &pixmapSize,
                                 const QColor &borderColor, qreal borderWidth)
    : QGraphicsWidget(), m_imageFilePath(imageFilePath),
      m_borderColor(borderColor), m_borderWidth(borderWidth) {

  // listen itemChange event
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);

  qreal devicePixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
  m_pixmap.setDevicePixelRatio(devicePixelRatio);
  m_pixmap.load(imageFilePath);

  QPixmap pixmap = m_pixmap.scaled(pixmapSize, Qt::KeepAspectRatioByExpanding,
                                   Qt::SmoothTransformation);

  m_previousRectSize = pixmapSize;

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

  // draw a border around the widget
  if (m_borderWidth > 0.0) {
    QPen pen;
    pen.setColor(m_borderColor);
    pen.setWidthF(m_borderWidth);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect().adjusted(0.0, 0.0, 0.0, 0.0));
  }
}

void ImageWidgetItem::setDesiredShadowEffectColor(
    const QColor &newDesiredShadowEffectColor) {
  m_desiredShadowEffectColor = newDesiredShadowEffectColor;

  updateShadowEffect();
}

void ImageWidgetItem::setDesiredShadowEffectBlurRadius(
    qreal newDesiredShadowEffectBlurRadius) {
  m_desiredShadowEffectBlurRadius = newDesiredShadowEffectBlurRadius;

  updateShadowEffect();
}

void ImageWidgetItem::setDesiredShadowEffectOffsetY(
    qreal newDesiredShadowEffectOffsetY) {
  m_desiredShadowEffectOffsetY = newDesiredShadowEffectOffsetY;

  updateShadowEffect();
}

void ImageWidgetItem::setDesiredShadowEffectOffsetX(
    qreal newDesiredShadowEffectOffsetX) {
  m_desiredShadowEffectOffsetX = newDesiredShadowEffectOffsetX;

  updateShadowEffect();
}

void ImageWidgetItem::updateShadowEffect() {
  if (this->graphicsEffect()) {
    QGraphicsDropShadowEffect *shadowEffect =
        dynamic_cast<QGraphicsDropShadowEffect *>(graphicsEffect());
    if (shadowEffect) {
      shadowEffect->setXOffset(m_desiredShadowEffectOffsetX);
      shadowEffect->setYOffset(m_desiredShadowEffectOffsetY);
      shadowEffect->setBlurRadius(m_desiredShadowEffectBlurRadius);
      shadowEffect->setColor(m_desiredShadowEffectColor);
    }
  }
}

QVariant ImageWidgetItem::itemChange(GraphicsItemChange change,
                                     const QVariant &value) {

  if (change == QGraphicsItem::ItemPositionHasChanged ||
      change == QGraphicsItem::ItemTransformHasChanged) {
    reload();
  }

  return QGraphicsItem::itemChange(change, value);
}

/**
 * call this whenever item's geometrychanges to load new verison of image
 *
 * @brief ImageWidgetItem::reload
 */
void ImageWidgetItem::reload() {
  // TODO: do this using thumbnail generator??
  QRectF newRect = boundingRect();
  QSizeF newRectSize = newRect.size();
  if (newRectSize != m_previousRectSize) {
    qDebug() << "Update pixmap" << newRectSize << m_previousRectSize;
    m_pixmapItem->setPixmap(m_pixmap.scaled(newRectSize.toSize(),
                                            Qt::KeepAspectRatioByExpanding,
                                            Qt::SmoothTransformation));
    m_previousRectSize = newRectSize;
    update();
  } else {
    qDebug() << "Skip Update pixmap";
  }
}

QColor ImageWidgetItem::borderColor() const { return m_borderColor; }

void ImageWidgetItem::setBorderWidth(qreal newBorderWidth) {
  m_borderWidth = newBorderWidth;
}

void ImageWidgetItem::setBorderColor(const QColor &newBorderColor) {
  m_borderColor = newBorderColor;
}

void ImageWidgetItem::toggleShadowEffect(bool turnOn) {
  QGraphicsDropShadowEffect *shadowEffect = nullptr;

  if (turnOn) {
    // Check if a QGraphicsEffect is already applied
    if (!this->graphicsEffect()) {
      shadowEffect = new QGraphicsDropShadowEffect;
      shadowEffect->setXOffset(m_desiredShadowEffectOffsetX);
      shadowEffect->setXOffset(m_desiredShadowEffectOffsetY);

      shadowEffect->setBlurRadius(m_desiredShadowEffectBlurRadius);
      shadowEffect->setColor(m_desiredShadowEffectColor);
      this->setGraphicsEffect(shadowEffect);
    }
  } else {
    // Remove the shadow effect from the QGraphicsItem
    if (this->graphicsEffect()) {
      this->setGraphicsEffect(nullptr);
    }
  }
}

QPainterPath ImageWidgetItem::shape() const
{

}
