#include "graphicsviewwidget.h"
#include "imagewidgetitem.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QScrollBar>
#include <QStyleOptionGraphicsItem>

GraphicsViewWidget::GraphicsViewWidget(QWidget *parent)
    : QGraphicsView(parent), m_scene(new GraphicsScene) {

  // setDragMode(QGraphicsView::RubberBandDrag);
  setDragMode(QGraphicsView::ScrollHandDrag);
  setResizeAnchor(QGraphicsView::AnchorUnderMouse);
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  setRenderHint(QPainter::Antialiasing, true);
  setRenderHint(QPainter::SmoothPixmapTransform, true);

  connect(m_scene, &QGraphicsScene::changed, this,
          [=](const QList<QRectF> &region) {
            Q_UNUSED(region);
            viewport()->update();
          });

  setScene(m_scene);
}

void GraphicsViewWidget::setCurrentPattern(PatternBase *newCurrentPattern) {
  m_currentPattern = newCurrentPattern;
}

PatternBase *GraphicsViewWidget::currentPattern() const {
  return m_currentPattern;
}

qreal GraphicsViewWidget::scaleFactor() const {
  return QStyleOptionGraphicsItem::levelOfDetailFromTransform(transform());
}

void GraphicsViewWidget::zoomView(qreal scaleFactor) {
  m_enableFitInView = false;
  scale(scaleFactor, scaleFactor);
}

void GraphicsViewWidget::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() == Qt::ControlModifier) {
    qreal zoomFactor = 1.10;

    if (event->angleDelta().y() > 0) {
      zoomView(zoomFactor);
    } else {
      zoomView(1.0 / zoomFactor);
    }

    event->accept();
  } else {
    QGraphicsView::wheelEvent(event);
  }
}

void GraphicsViewWidget::resizeEvent(QResizeEvent *event) {
  if (m_enableFitInView) {
    qreal gap = 20.0;

    QRectF newRect = QRectF(-gap, -gap, sceneRect().width() + 2 * gap,
                            sceneRect().height() + 2 * gap);

    this->fitInView(newRect, Qt::KeepAspectRatio);
  }

  QGraphicsView::resizeEvent(event);
}

void GraphicsViewWidget::viewSetCustomSize(const QSize &size) {

  m_scene->setSceneRect(0, 0, size.width(), size.height());

  setScene(m_scene);

  scene()->updateScaledBackgroundPixmap();
}

GraphicsScene *GraphicsViewWidget::scene() const { return m_scene; }
