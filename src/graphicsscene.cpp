#include "graphicsscene.h"

#include <QGuiApplication>
#include <QPainterPath>
#include <QScreen>

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene{parent} {

}

void GraphicsScene::setBackgroundColor(const QColor &color) {
  m_backgroundType = BackgroundType::Color;
  m_backgroundColor = color;
  update();
}

void GraphicsScene::setBackgroundImage(const QString &imagePath) {
  m_backgroundType = BackgroundType::Image;
  m_backgroundImage = QPixmap(imagePath);
  m_backgroundImage.setDevicePixelRatio(
      QGuiApplication::primaryScreen()->devicePixelRatio());
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

QSize GraphicsScene::scaleSize(const QSize &originalSize, double scaleFactor) {
  int newWidth = static_cast<int>(originalSize.width() * scaleFactor);
  int newHeight = static_cast<int>(originalSize.height() * scaleFactor);
  return QSize(newWidth, newHeight);
}

void GraphicsScene::updateScaledBackgroundPixmap() {
  if (!m_backgroundImage.isNull()) {
      QSizeF targetSizeF_ = sceneRect().size();
      QSize targetSizeF = scaleSize(targetSizeF_.toSize(), m_tiledBgScaleFactor);

      m_scaledBackgroundPixmap = m_backgroundImage.scaled(
          targetSizeF, Qt::KeepAspectRatio, Qt::SmoothTransformation);
      m_scaledBackgroundPixmap.setDevicePixelRatio(QGuiApplication::primaryScreen()->devicePixelRatio());
  }
}

void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect) {

  switch (m_backgroundType) {
  case GraphicsScene::BackgroundType::None:
    painter->fillRect(rect, Qt::transparent);
    break;
  case BackgroundType::Color:
    if (!m_backgroundColor.isValid()) {
      painter->fillRect(rect, Qt::gray);
    } else {
      painter->fillRect(rect, m_backgroundColor);
    }
    break;
  case BackgroundType::Image:
    if (!m_backgroundImage.isNull()) {

      QSizeF targetSizeF_ = rect.size();

      QSize targetSizeF =
          scaleSize(targetSizeF_.toSize(), m_tiledBgScaleFactor);

      // Calculate the scaled size while maintaining the aspect ratio
      QSize scaledSize = m_scaledBackgroundPixmap.rect().size();

      if (m_backgroundImageTiled) {

        // Create a painter path that tiles the image if it doesn't fit the scene
        QPainterPath path;
        path.addRect(rect);
        //painter->setClipPath(path);

        // Draw the tiled image
        for (int x = rect.left(); x < rect.right(); x += scaledSize.width()) {
          for (int y = rect.top(); y < rect.bottom();
               y += scaledSize.height()) {
            painter->drawPixmap(QPoint(x, y), m_scaledBackgroundPixmap);
          }
        }

        //painter->setClipping(false);
      } else {
        // Calculate the position to center the image within the target
        // rectangle
        QPoint targetPos((targetSizeF.width() - scaledSize.width()) / 2,
                         (targetSizeF.height() - scaledSize.height()) / 2);

        // draw image at center
        painter->drawPixmap(targetPos, m_scaledBackgroundPixmap);
      }
    }
    break;
  case BackgroundType::Gradient:
    if (!m_backgroundGradient.stops().isEmpty()) {
      painter->fillRect(rect, QBrush(m_backgroundGradient));
    }
    break;
  case BackgroundType::Transparent:
    painter->fillRect(rect, Qt::transparent);
    break;
  }

  QGraphicsScene::drawBackground(painter, rect);
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
