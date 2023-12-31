#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "imagewidgetitem.h"

#include <QColor>
#include <QGraphicsScene>
#include <QLinearGradient>
#include <QObject>
#include <QPainter>
#include <QPixmap>

class GraphicsScene : public QGraphicsScene {
  Q_OBJECT

public:
  enum class BackgroundType { None, Color, Image, Gradient, Transparent };

  explicit GraphicsScene(QObject *parent = nullptr);

  void setBackgroundGradient(const QLinearGradient &gradient);
  void setBackgroundImage(const QString &imagePath);
  void setBackgroundColor(const QColor &color);
  void setTransparentBackground();
  QColor getBackgroundColor() const;
  QPixmap getBackgroundImage() const;
  QLinearGradient getBackgroundGradient() const;
  GraphicsScene::BackgroundType getBackgroundType() const;
  void setBackgroundImageTiled(bool newBackgroundImageTiled);
  void setTiledBgScaleFactor(double newTiledBgScaleFactor);
  void resetTiledBgScaleFactor();
  double tiledBgScaleFactor() const;
  void updateScaledBackgroundPixmap();
  void setCheckerboardEnabled(bool enabled, bool invertColor = true);
  void addImageItemWidget(ImageWidgetItem *imageWidgetItem = nullptr);
  void clearItemWidgets();
  QList<ImageWidgetItem *> imageWidgetItemsContainer() const;

  void setBackgroundImageBlurRadius(qreal newBackgroundImageBlurRadius);

protected:
  void drawBackground(QPainter *painter, const QRectF &rect_) override;

private:
  BackgroundType m_backgroundType = BackgroundType::None;
  QColor m_backgroundColor;
  QPixmap m_backgroundImage;
  QColor m_backgroundImageDominantColor;
  qreal m_backgroundImageBlurRadius = 0.0;
  QPixmap m_scaledBackgroundPixmap;
  QLinearGradient m_backgroundGradient;
  bool m_backgroundImageTiled;
  double m_tiledBgScaleFactor = 1.0;
  QList<ImageWidgetItem *> m_imageWidgetItemsContainer;

  QSize scaleSize(const QSize &originalSize, double scaleFactor);
};

#endif // GRAPHICSSCENE_H
