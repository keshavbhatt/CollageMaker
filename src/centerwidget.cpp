#include "centerwidget.h"
#include "ui_centerwidget.h"

#include <QDebug>
#include <QDir>
#include <QGraphicsTextItem>

CenterWidget::CenterWidget(GraphicsViewWidget *graphicsViewWidget,
                           QWidget *parent)
    : QWidget(parent), ui(new Ui::CenterWidget),
      p_graphicsViewWidget(graphicsViewWidget) {

  ui->setupUi(this);

  ui->graphicsViewLayout->addWidget(p_graphicsViewWidget);

}

CenterWidget::~CenterWidget() { delete ui; }

void CenterWidget::on_pushButton_clicked() {

  // do not render selection rect to the file
  p_graphicsViewWidget->scene()->clearSelection();

  // if transparent mode is on, do not render checkboxes to the file by
  // temporary setting transparent color to background, later we restore it
  bool restoreTransparentBrush =
      (p_graphicsViewWidget->scene()->getBackgroundType() ==
       GraphicsScene::BackgroundType::Transparent);

  p_graphicsViewWidget->scene()->setCheckerboardEnabled(
      !restoreTransparentBrush);

  auto oldBackgroundColor = p_graphicsViewWidget->scene()->getBackgroundColor();

  if (restoreTransparentBrush) {
    p_graphicsViewWidget->scene()->setBackgroundColor(Qt::transparent);
  }

  // create the image with the exact size of the shrunk scene
  QImage image(p_graphicsViewWidget->scene()->sceneRect().size().toSize(),
               QImage::Format_ARGB32);

  // start all pixels transparent
  image.fill(Qt::transparent);

  QPainter painter(&image);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

  p_graphicsViewWidget->scene()->render(&painter);
  painter.end();

  image.save("scene_image.png");

  // restore color and transparent mode
  if (restoreTransparentBrush) {
    p_graphicsViewWidget->scene()->setBackgroundColor(oldBackgroundColor);
    p_graphicsViewWidget->scene()->setTransparentBackground();
  }
}

GraphicsViewWidget *CenterWidget::graphicsViewWidget() const {
  return p_graphicsViewWidget;
}
