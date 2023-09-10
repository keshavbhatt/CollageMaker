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

  ui->scrollAreaWidgetContents->layout()->addWidget(p_graphicsViewWidget);

  // add p_graphicsViewWidget and align at center
  QVBoxLayout *parentLayout =
      qobject_cast<QVBoxLayout *>(ui->scrollAreaWidgetContents->layout());
  if (parentLayout) {

    QSpacerItem *verticalSpacerTop =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    parentLayout->addSpacerItem(verticalSpacerTop);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(p_graphicsViewWidget);
    horizontalLayout->addStretch();

    parentLayout->addLayout(horizontalLayout);

    QSpacerItem *verticalSpacerBottom =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    parentLayout->addSpacerItem(verticalSpacerBottom);
  }
}

CenterWidget::~CenterWidget() { delete ui; }

void CenterWidget::on_pushButton_clicked() {
  QImage image(p_graphicsViewWidget->size(), QImage::Format_ARGB32);
  image.fill(Qt::transparent);

  QPainter painter(&image);
  p_graphicsViewWidget->render(&painter);
  painter.end();

  image.save("scene_image.png");
}

GraphicsViewWidget *CenterWidget::graphicsViewWidget() const {
  return p_graphicsViewWidget;
}
