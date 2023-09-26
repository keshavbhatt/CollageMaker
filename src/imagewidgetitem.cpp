#include "imagewidgetitem.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGuiApplication>
#include <QImageReader>
#include <QScreen>

ImageWidgetItem::ImageWidgetItem(const QString &imageFilePath,
                                 const QRectF &itemBoundingRect,
                                 const QColor &borderColor, qreal borderWidth)
    : QGraphicsItem(), m_previousRectF(itemBoundingRect),
      m_imageFilePath(imageFilePath), m_desiredBorderColor(borderColor),
      m_desiredBorderWidth(borderWidth) {

  // listen itemChange event
  setFlag(QGraphicsItem::ItemSendsGeometryChanges);

  qreal devicePixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
  m_pixmap.setDevicePixelRatio(devicePixelRatio);
  m_pixmap.load(imageFilePath);

  //  m_pixmap =
  //      m_pixmap.transformed(QTransform().scale(-1, 1),
  //      Qt::SmoothTransformation);
}

QRectF ImageWidgetItem::boundingRect() const { return m_previousRectF; }

/**
 * call this whenever item's geometrychanges to load new verison of image
 *
 * @brief ImageWidgetItem::reload
 */
void ImageWidgetItem::reload(QRectF newRectF) {
  if (newRectF != m_previousRectF) {
    qDebug() << "Update pixmap" << newRectF << m_previousRectF;
    m_previousRectF = newRectF;
    update(); // force repaint
  } else {
    qDebug() << "Skip Update pixmap";
  }
}

void ImageWidgetItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);

  // Calculate the destination rectangle for drawing the pixmap
  QRectF targetRect = boundingRect();

  // Create a QPainterPath for the rounded rectangle clipping path
  if (m_desiredBorderCornerSize > 0.0) {
    QPainterPath clipPath;
    clipPath.addRoundedRect(targetRect, m_desiredBorderCornerSize,
                            m_desiredBorderCornerSize);
    painter->setClipPath(clipPath);
  }

  // Draw the pixmap on the widget
  QPixmap centeredPixmap = getCenterPixelRegion(m_pixmap, targetRect.size());
  if (!centeredPixmap.isNull()) {
    QRectF sourceRect = centeredPixmap.rect();

    // Draw the pixmap, scaling it to fit the adjusted target rectangle
    painter->drawPixmap(targetRect.toRect(), centeredPixmap,
                        sourceRect.toRect());
  }

  // Draw a border around the adjusted target rectangle
  if (m_desiredBorderWidth > 0.0) {
    QPen pen;
    pen.setColor(m_desiredBorderColor);
    pen.setWidthF(m_desiredBorderWidth);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    // Draw a rounded rectangle if the corner size is greater than 0
    if (m_desiredBorderCornerSize > 0.0) {
      painter->drawRoundedRect(targetRect.toRect(), m_desiredBorderCornerSize,
                               m_desiredBorderCornerSize);
    } else {
      painter->drawRect(targetRect.toRect());
    }
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

  QRectF newRectF = boundingRect();
  if (newRectF != m_previousRectF) {
    reload(newRectF);
    m_previousRectF = newRectF;
  }

  return QGraphicsItem::itemChange(change, value);
}

void ImageWidgetItem::setDesiredBorderCornerSize(
    qreal newDesiredBorderCornerSize) {
  m_desiredBorderCornerSize = newDesiredBorderCornerSize;

  update();
}

void ImageWidgetItem::setBorderWidth(qreal newBorderWidth) {
  m_desiredBorderWidth = newBorderWidth;
}

void ImageWidgetItem::setBorderColor(const QColor &newBorderColor) {
  m_desiredBorderColor = newBorderColor;
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

/**
 * Return pixmap of asked size from center of original Pixmap.
 *
 * Fills reagion with transparent background if size is bigger then
 * originalPixmap bounds.
 *
 * more precise version, operates on qreal values
 *
 * @brief ImageWidgetItem::getCenterPixelRegion
 * @param originalPixmap
 * @param size
 * @return
 */
QPixmap
ImageWidgetItem::getCenterPixelRegionIntPrecesion(const QPixmap &originalPixmap,
                                                  const QSizeF size) {
  QPixmap centerRegion(size.toSize());
  centerRegion.fill(Qt::transparent);

  int x = (originalPixmap.width() - size.width()) / 2;
  int y = (originalPixmap.height() - size.height()) / 2;

  QPainter painter(&centerRegion);
  painter.drawPixmap(0, 0, originalPixmap, x, y, size.width(), size.height());

  return centerRegion;
}

/**
 * Return pixmap of asked size from center of original Pixmap.
 *
 * Fills reagion with transparent background if size is bigger then
 * originalPixmap bounds.
 *
 * more precise version, operates on qreal values
 *
 * @brief ImageWidgetItem::getCenterPixelRegion
 * @param originalPixmap
 * @param size
 * @return
 */
QPixmap
ImageWidgetItem::getCenterPixelRegionExact(const QPixmap &originalPixmap,
                                           const QSizeF size) {
  QPixmap centerRegion(size.toSize());
  centerRegion.fill(Qt::transparent);

  int x = qRound((originalPixmap.width() - size.width()) / 2.0);
  int y = qRound((originalPixmap.height() - size.height()) / 2.0);

  QPainter painter(&centerRegion);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setRenderHint(QPainter::TextAntialiasing, false);

  painter.drawPixmap(0, 0, originalPixmap, x, y, size.width(), size.height());

  return centerRegion;
}

/**
 * Return pixmap of asked size from center of original Pixmap.
 *
 * Also scales image if asked size is not in bounds of originalPixmap
 *
 * @brief ImageWidgetItem::getCenterPixelRegion
 * @param originalPixmap
 * @param size
 * @return
 */
QPixmap ImageWidgetItem::getCenterPixelRegion(const QPixmap &originalPixmap,
                                              const QSizeF requestedSize) {
  // Get the size of the original pixmap
  QSize originalSize = originalPixmap.size();

  // Check if scaling is needed by comparing both height and width
  bool needsScaling = (requestedSize.width() != originalSize.width() ||
                       requestedSize.height() != originalSize.height());

  if (needsScaling) {
    // Calculate the scaling factors for width and height to fit the requested
    // size
    qreal widthScaleFactor =
        static_cast<qreal>(requestedSize.width()) / originalSize.width();
    qreal heightScaleFactor =
        static_cast<qreal>(requestedSize.height()) / originalSize.height();

    // Choose the maximum of these two scaling factors to ensure the image fits
    // the requested size
    qreal scaleFactor = qMax(widthScaleFactor, heightScaleFactor);

    // Calculate the target size after scaling
    int targetWidth = static_cast<int>(originalSize.width() * scaleFactor);
    int targetHeight = static_cast<int>(originalSize.height() * scaleFactor);

    // Scale the original pixmap to the target size
    QPixmap scaledPixmap =
        originalPixmap.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio,
                              Qt::SmoothTransformation);

    // Calculate the center rectangle to crop from the scaled pixmap
    QRect cropRect((scaledPixmap.width() - requestedSize.width()) / 2,
                   (scaledPixmap.height() - requestedSize.height()) / 2,
                   requestedSize.width(), requestedSize.height());

    // Crop the scaled pixmap to the requested size and centered portion
    QPixmap croppedPixmap = scaledPixmap.copy(cropRect);

    return croppedPixmap;
  } else {
    // No scaling is needed, just calculate the center rectangle to crop from
    // the original image
    QRect cropRect((originalSize.width() - requestedSize.width()) / 2,
                   (originalSize.height() - requestedSize.height()) / 2,
                   requestedSize.width(), requestedSize.height());

    // Crop the original pixmap to the requested size and centered portion
    QPixmap croppedPixmap = originalPixmap.copy(cropRect);

    return croppedPixmap;
  }
}
