#include "graphicsviewwidget.h"

#include <QDebug>

GraphicsViewWidget::GraphicsViewWidget(QWidget *parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene) {

  setFrameStyle(QFrame::NoFrame);
  setScene(m_scene);

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GraphicsViewWidget::addPixmapItem(const QString &imageFilePath) {
  QGraphicsPixmapItem *pixmapItem =
      m_scene->addPixmap(QPixmap(imageFilePath)
                             .scaled(QSize(400, 400), Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation));

  pixmapItem->setFlags(
      QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
      QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemClipsToShape |
      QGraphicsItem::ItemClipsChildrenToShape);
}

void GraphicsViewWidget::setCustomSize(const QSize &size) {
  setFixedSize(size);
  scene()->setSceneRect(0, 0, size.width(), size.height());
}
