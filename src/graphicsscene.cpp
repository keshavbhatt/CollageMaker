#include "graphicsscene.h"

#include <QDebug>
#include <QGuiApplication>
#include <QPainterPath>
#include <QScreen>

// TODO: remove this once we drop older Qt support.
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
#define COMPAT_CONSTCOLOR constexpr
#else
#define COMPAT_CONSTCOLOR const
#endif

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene{parent} {}

void GraphicsScene::setBackgroundColor(const QColor &color) {
  m_backgroundType = BackgroundType::Color;
  m_backgroundColor = color;
  update();
}

void GraphicsScene::setBackgroundImage(const QString &imagePath) {
  qreal devicePixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();

  m_backgroundType = BackgroundType::Image;
  m_backgroundImage = QPixmap(imagePath);
  m_backgroundImage.setDevicePixelRatio(devicePixelRatio);
  updateScaledBackgroundPixmap();
  update();
}

void GraphicsScene::setBackgroundGradient(const QLinearGradient &gradient) {
  m_backgroundType = BackgroundType::Gradient;
  m_backgroundGradient = gradient;
  update();
}

void GraphicsScene::setTransparentBackground() {
  m_backgroundType = BackgroundType::Transparent;
  update();
}

void GraphicsScene::setCheckerboardEnabled(bool enabled, bool invertColor) {
  if (enabled) {
    QPixmap tilePixmap(0x20, 0x20);
    tilePixmap.fill(invertColor ? QColor(220, 220, 220, 170)
                                : QColor(35, 35, 35, 170));
    QPainter tilePainter(&tilePixmap);
    COMPAT_CONSTCOLOR QColor color(45, 45, 45, 170);
    COMPAT_CONSTCOLOR QColor invertedColor(210, 210, 210, 170);
    tilePainter.fillRect(0, 0, 0x10, 0x10, invertColor ? invertedColor : color);
    tilePainter.fillRect(0x10, 0x10, 0x10, 0x10,
                         invertColor ? invertedColor : color);
    tilePainter.end();

    setBackgroundBrush(tilePixmap);
  } else {
    setBackgroundBrush(Qt::transparent);
  }
}

void GraphicsScene::clearItemWidgets() {
  this->clear();
  m_imageWidgetItemsContainer.clear();
}

void GraphicsScene::addImageItemWidget(ImageWidgetItem *imageWidgetItem) {
  if (imageWidgetItem != nullptr) {
    qDebug() << imageWidgetItem->rect();
    this->addItem(imageWidgetItem);
    update();

    m_imageWidgetItemsContainer.append(imageWidgetItem);
  }
}

QSize GraphicsScene::scaleSize(const QSize &originalSize, double scaleFactor) {
  int newWidth = static_cast<int>(originalSize.width() * scaleFactor);
  int newHeight = static_cast<int>(originalSize.height() * scaleFactor);
  return QSize(newWidth, newHeight);
}

QList<ImageWidgetItem *> GraphicsScene::imageWidgetItemsContainer() const {
  return m_imageWidgetItemsContainer;
}

void GraphicsScene::updateScaledBackgroundPixmap() {
  if (!m_backgroundImage.isNull()) {
    QSizeF targetSizeF_ = sceneRect().size();
    QSize targetSizeF = scaleSize(targetSizeF_.toSize(), m_tiledBgScaleFactor);

    m_scaledBackgroundPixmap = m_backgroundImage.scaled(
        targetSizeF, Qt::KeepAspectRatio, Qt::SmoothTransformation);
  }
}

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect_) {

  Q_UNUSED(rect_);

  const QRectF sceneRectF = sceneRect();

  setCheckerboardEnabled(getBackgroundType() == BackgroundType::Transparent);

  switch (m_backgroundType) {
  case GraphicsScene::BackgroundType::None:
    painter->fillRect(sceneRectF, Qt::transparent);
    break;
  case BackgroundType::Color:
    if (!m_backgroundColor.isValid()) {
      painter->fillRect(sceneRectF, Qt::gray);
    } else {
      painter->fillRect(sceneRectF, m_backgroundColor);
    }
    break;
  case BackgroundType::Image:
    if (!m_backgroundImage.isNull()) {

      // Calculate the scaled size while maintaining the aspect ratio
      QSize scaledSize = m_scaledBackgroundPixmap.rect().size();

      if (m_backgroundImageTiled) {

        // Create a painter path that tiles the image if it doesn't fit the
        // scene
        QPainterPath path;
        path.addRect(sceneRectF);
        painter->setClipPath(path);

        // draw the tiled image
        for (int x = sceneRectF.left(); x < sceneRectF.right();
             x += scaledSize.width()) {
          for (int y = sceneRectF.top(); y < sceneRectF.bottom();
               y += scaledSize.height()) {
            painter->drawPixmap(QPoint(x, y), m_scaledBackgroundPixmap);
          }
        }
        painter->setClipping(false);
      } else {

        QPainterPath path;
        path.addRect(sceneRectF);
        painter->setClipPath(path);

        // draw image at scene's x ,y coordinates
        painter->drawPixmap(QPoint(sceneRectF.x(), sceneRectF.y()),
                            m_scaledBackgroundPixmap);

        painter->setClipping(false);
      }
    }
    break;
  case BackgroundType::Gradient:
    if (!m_backgroundGradient.stops().isEmpty()) {
      painter->fillRect(sceneRectF, QBrush(m_backgroundGradient));
    }
    break;
  case BackgroundType::Transparent:
    painter->fillRect(sceneRectF, Qt::transparent);
    break;
  }

  QGraphicsScene::drawBackground(painter, sceneRectF);
}

double GraphicsScene::tiledBgScaleFactor() const {
  return m_tiledBgScaleFactor;
}

void GraphicsScene::resetTiledBgScaleFactor() { setTiledBgScaleFactor(1.0); }

void GraphicsScene::setTiledBgScaleFactor(double newTiledBgScaleFactor) {
  m_tiledBgScaleFactor = newTiledBgScaleFactor;
  updateScaledBackgroundPixmap();
  update();
}

void GraphicsScene::setBackgroundImageTiled(bool newBackgroundImageTiled) {
  m_backgroundImageTiled = newBackgroundImageTiled;
  update();
}

GraphicsScene::BackgroundType GraphicsScene::getBackgroundType() const {
  return m_backgroundType;
}

QLinearGradient GraphicsScene::getBackgroundGradient() const {
  return m_backgroundGradient;
}

QPixmap GraphicsScene::getBackgroundImage() const { return m_backgroundImage; }

QColor GraphicsScene::getBackgroundColor() const { return m_backgroundColor; }
