#include "mosaicpattern.h"
#include "ui_mosaicpattern.h"

#include <QDebug>

MosaicPattern::MosaicPattern(GraphicsViewWidget *graphicsViewWidget,
                             LayoutWidget *layoutWidget,
                             PictureSettings *pictureSettings,
                             PictureShadowSettings *pictureShadowSettings,
                             QWidget *parent)
    : PatternBase(parent), ui(new Ui::MosaicPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget),
      p_pictureSettings(pictureSettings),
      p_pictureShadowSettings(pictureShadowSettings) {
  ui->setupUi(this);

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
}

MosaicPattern::~MosaicPattern() { delete ui; }

//================START LAYOUT======================

void MosaicPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutProperties();
}

//================END LAYOUT======================

void MosaicPattern::applyBackgroundProperties() {
  p_layoutWidget->applyBackgroundSettings();
}

void MosaicPattern::applyPictureProperties() {
  p_pictureSettings->applySettings();
}

void MosaicPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
  ui->pictureSettingsPlaceholder->addWidget(p_pictureSettings);
  ui->pictureShadowPlaceholder->addWidget(p_pictureShadowSettings);
}

void MosaicPattern::reload() {
  QList<ImageWidgetItem *> imageWidgetItemsContainer =
      p_graphicsViewWidget->scene()->imageWidgetItemsContainer();

  if (!imageWidgetItemsContainer.isEmpty()) {

    qDebug() << "Mossaic Pattern: Reload()";

    const int numImages = imageWidgetItemsContainer.count();

    // MOSSAIC PATTERN SPECIFIC
    MosaicUtils::MosaicLayout layout = MosaicUtils::generateMosaicLayout(
        numImages, p_graphicsViewWidget->sceneRect().size(), 20.0);

    for (int i = 0; i < numImages; ++i) {
      ImageWidgetItem *imageItemWidget = imageWidgetItemsContainer.at(i);
      imageItemWidget->reload(layout.itemsRects.at(i));
    }
  }
}

void MosaicPattern::addPixmapItemsToView(const QStringList &imagePaths) {
  // required to block unnecessary empty requets
  if (imagePaths.empty())
    return;
}

void MosaicPattern::prepare() {}

void MosaicPattern::apply() {

  this->applyLayoutProperties();

  this->applyBackgroundProperties();

  this->reload();
}
