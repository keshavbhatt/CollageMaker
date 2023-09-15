#include "graphicsviewwidget.h"

#include <QDebug>

GraphicsViewWidget::GraphicsViewWidget(QWidget *parent)
    : QGraphicsView(parent), m_scene(new GraphicsScene) {

  // hide scrollbars, in addition we also disable the wheelevent on the view
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // setFrameStyle(QFrame::NoFrame);

  connect(m_scene, &QGraphicsScene::changed, this,
          [=](const QList<QRectF> &region) {
            Q_UNUSED(region);
            // This slot will be called whenever something in the scene changes.
            // The 'region' parameter contains the area that was affected by the
            // change.

            // You can put code here to handle changes in the scene.
            // For example, you can call viewport()->update(); to refresh the
            // view.
            viewport()->update();
          });

  setScene(m_scene);
}

void GraphicsViewWidget::wheelEvent(QWheelEvent *event) {
  //  // Prevent scrolling by ignoring the wheel event
  event->ignore();
}

void GraphicsViewWidget::addPixmapItem(const QString &imageFilePath) {
  QGraphicsPixmapItem *pixmapItem =
      m_scene->addPixmap(QPixmap(imageFilePath)
                             .scaled(QSize(400, 400), Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation));

  pixmapItem->setFlags(
      QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable |
      QGraphicsItem::ItemIsFocusable /*| QGraphicsItem::ItemClipsToShape |
      QGraphicsItem::ItemClipsChildrenToShape*/);
}

/**
 * Set fixed width and height of widget using the size supplied.
 * This also update the scene to have same size as view.
 *
 * @brief GraphicsViewWidget::setCustomSize
 * @param size
 */
void GraphicsViewWidget::viewSetCustomSize(const QSize &size) {

  setFixedSize(size);
  // Adjust the scene rect to match the size of the viewport's rect
  scene()->setSceneRect(0, 0, size.width(), size.height());
  scene()->updateScaledBackgroundPixmap();

//  qDebug() << "Custom Size:" << size;
//  qDebug() << "Scene Rect:" << scene()->sceneRect();
}

GraphicsScene *GraphicsViewWidget::scene() const { return m_scene; }
