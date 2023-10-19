#include "gridpattern.h"
#include "ui_gridpattern.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <imagewidgetitem.h>

#include <utils/commonutils.h>
#include <utils/gridutils.h>

GridPattern::GridPattern(GraphicsViewWidget *graphicsViewWidget,
                         LayoutWidget *layoutWidget,
                         PictureSettings *pictureSettings,
                         PictureShadowSettings *pictureShadowSettings,
                         QWidget *parent)
    : PatternBase(parent), ui(new Ui::GridPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget),
      p_pictureSettings(pictureSettings),
      p_pictureShadowSettings(pictureShadowSettings) {

  ui->setupUi(this);

  //========== START UI CONNECTIONS ====================
  connect(ui->spaceingSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredSpacing);

  connect(ui->rowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setDesiredRows);

  connect(ui->columnSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setDesiredColumns);

  connect(ui->layoutPresetsComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &GridPattern::setLayoutPreset);

  connect(ui->presetSwapButton, &QPushButton::clicked, this,
          &GridPattern::swapRowColumn);

  connect(ui->presetBestFitButton, &QPushButton::clicked, this,
          &GridPattern::setBestRowColumn);

  //========== END UI CONNECTIONS ====================

  // rows/cols
  ui->rowsSpinBox->setMinimum(1);
  ui->columnSpinBox->setMinimum(1);

  // spacing
  ui->spaceingSlider->setRange(0, 999);
  ui->spaceingSlider->setValue(1);
  ui->spaceingSlider->setValue(0);
}

GridPattern::~GridPattern() { delete ui; }

//================START LAYOUT======================

void GridPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutProperties();
}

//================END LAYOUT======================

void GridPattern::applyBackgroundProperties() {
  p_layoutWidget->applyBackgroundSettings();
}

void GridPattern::applyPictureProperties() {
  p_pictureSettings->applySettings();
}

void GridPattern::applyPictureShadowProperties() {
  p_pictureShadowSettings->applySettings();
}

void GridPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
  ui->pictureSettingsPlaceholder->addWidget(p_pictureSettings);
  ui->pictureShadowPlaceholder->addWidget(p_pictureShadowSettings);
}

void GridPattern::updateLayoutPresetComboBox(
    QList<QPair<int, int>> gridVariants) {
  ui->layoutPresetsComboBox->clear();

  for (const QPair<int, int> &pair : gridVariants) {
    QString itemText = QString("%1x%2").arg(pair.first).arg(pair.second);
    QVariant variant;
    variant.setValue(pair);
    ui->layoutPresetsComboBox->addItem(itemText, variant);
  }
}

void GridPattern::addAdditionalImageWidgetItems(
    const int additionalItemsCount) {
  QStringList emptyPaths;
  emptyPaths.append(m_loadedImagePaths);
  for (int i = 0; i < additionalItemsCount; ++i) {
    emptyPaths.append(QString(""));
  }
  this->addPixmapItemsToView(emptyPaths);
}

void GridPattern::reload() {

  QList<ImageWidgetItem *> imageWidgetItemsContainer =
      p_graphicsViewWidget->scene()->imageWidgetItemsContainer();

  if (!imageWidgetItemsContainer.isEmpty()) {

    qDebug() << "Grid Pattern: Reload()";

    const int numImages = m_desiredRows * m_desiredColumns;

    // GRID PATTERN SPECIFIC
    GridUtils::GridInfo gridInfo = GridUtils::calculateCellSizeForItemCount(
        p_graphicsViewWidget->sceneRect().size(), numImages, m_desiredSpacing,
        m_desiredRows, m_desiredColumns);

    // add/remove additional items if required
    const int newImageWidgetCount = gridInfo.rows * gridInfo.columns;
    const int oldImageCount = imageWidgetItemsContainer.count();
    if (newImageWidgetCount > oldImageCount) {
      const int requiredItems = newImageWidgetCount - oldImageCount;
      this->addAdditionalImageWidgetItems(requiredItems);
      return;
    } else if (newImageWidgetCount < oldImageCount) {

      for (int i = 0; i < m_loadedImagePaths.count(); ++i) {
        auto item = m_loadedImagePaths.at(i);
        if (item.isEmpty()) {
          m_loadedImagePaths.removeAt(i);
        }
      }
      QStringList newLoadedImagePaths;
      newLoadedImagePaths.append(m_loadedImagePaths);
      m_loadedImagePaths.clear();
      this->addPixmapItemsToView(newLoadedImagePaths);
      return;
    }

    this->updateRowsColsSielently(gridInfo.rows, gridInfo.columns);

    for (int i = 0; i < numImages; ++i) {
      ImageWidgetItem *imageItemWidget = imageWidgetItemsContainer.at(i);

      // pixmap item
      imageItemWidget->reload(
          QRectF(gridInfo.itemPositions.at(i).toPoint(), gridInfo.cellSize));

      // hack to fix border when drop shadow is enabled
      // NOTE: keep this above corner setting always
      if (p_pictureShadowSettings->shadowEnabled()) {
        if (p_pictureSettings->desiredBorderCornerSize() == 0.0)
          p_pictureSettings->setDesiredBorderCornerSize(0.1);
      } else {
        if (p_pictureSettings->desiredBorderCornerSize() == 0.1)
          p_pictureSettings->setDesiredBorderCornerSize(0.0);
      }
    }
  }
}

void GridPattern::apply() {

  this->applyLayoutProperties();

  this->applyBackgroundProperties();

  this->applyPictureProperties();

  this->applyPictureShadowProperties();
}

void GridPattern::addPixmapItemsToView(const QStringList &imagePaths) {

  // required to block unnecessary empty requets
  if (imagePaths.empty())
    return;

  p_graphicsViewWidget->scene()->clearItemWidgets();

  m_loadedImagePaths = imagePaths;

  const int numImages = m_loadedImagePaths.count();

  // TODO: add images to random postion at begining and
  // handle the layout specific stuff in reload method
  // we should move this method to scene and from there
  // call current pattern reload.

  // GRID LAYOUT SPECIFIC
  QList<QPair<int, int>> gridVariants =
      GridUtils::findGridRowColumnCombinations(numImages);

  if (gridVariants.isEmpty() == false) {

    this->updateLayoutPresetComboBox(gridVariants);

    QPair<int, int> bestGrid = gridVariants.first();

    int rowCount = m_desiredRows == 0 ? bestGrid.first : m_desiredRows;
    int columnCount =
        m_desiredColumns == 0 ? bestGrid.second : m_desiredColumns;

    GridUtils::GridInfo gridInfo = GridUtils::calculateCellSizeForItemCount(
        p_graphicsViewWidget->sceneRect().size(), numImages, m_desiredSpacing,
        rowCount, columnCount);

    this->updateRowsColsSielently(gridInfo.rows, gridInfo.columns);

    for (int i = 0; i < numImages; ++i) {
      addPixmapItem(m_loadedImagePaths.at(i),
                    gridInfo.itemPositions.at(i).toPoint(), gridInfo.cellSize);
    }

    this->reload();
  }
}

void GridPattern::addPixmapItem(const QString &imageFilePath, QPointF position,
                                QSizeF imageWidgetSize) {
  ImageWidgetItem *imageWidgetItem =
      new ImageWidgetItem(imageFilePath, QRectF(position, imageWidgetSize),
                          p_pictureSettings->desiredBorderColor(),
                          p_pictureSettings->desiredBorderWidth());

  imageWidgetItem->setFlags(QGraphicsItem::ItemSendsScenePositionChanges |
                            QGraphicsItem::ItemIsMovable |
                            QGraphicsItem::ItemIsSelectable);

  p_graphicsViewWidget->scene()->addImageItemWidget(imageWidgetItem);
}

void GridPattern::prepare() {
  m_desiredRows = 0;
  m_desiredColumns = 0;
}

void GridPattern::updateRowsColsSielently(int rowCount, int columnCount) {

  ui->rowsSpinBox->blockSignals(true);
  ui->rowsSpinBox->setValue(rowCount);
  ui->rowsSpinBox->blockSignals(false);

  ui->columnSpinBox->blockSignals(true);
  ui->columnSpinBox->setValue(columnCount);
  ui->columnSpinBox->blockSignals(false);
}

void GridPattern::setLayoutPreset(int index) {

  QVariant data = ui->layoutPresetsComboBox->itemData(index);
  if (data.canConvert<QPair<int, int>>()) {
    QPair<int, int> pair = data.value<QPair<int, int>>();

    m_desiredRows = pair.first;
    m_desiredColumns = pair.second;

    ui->presetSwapButton->setEnabled((m_desiredRows != m_desiredColumns));
  }

  this->reload();
}

void GridPattern::setDesiredSpacing(qreal newDesiredSpacing) {

  m_desiredSpacing = CommonUtils::sliderValueToReal(
      0.0, 400.0, ui->spaceingSlider->maximum(), newDesiredSpacing);

  ui->spaceingLabel->setText(QString::number(m_desiredSpacing, 'f', 2));

  this->reload();
}

void GridPattern::setDesiredColumns(int newDesiredColumns) {

  //  int rowsCount = ui->rowsSpinBox->value();

  //  if (newDesiredColumns * rowsCount < m_loadedImagePaths.count()) {
  //    return;
  //  }

  m_desiredRows = ui->rowsSpinBox->value();
  m_desiredColumns = newDesiredColumns;

  this->reload();
}

void GridPattern::setDesiredRows(int newDesiredRows) {

  //  int columnsCount = ui->columnSpinBox->value();

  //  if (newDesiredRows * columnsCount < m_loadedImagePaths.count()) {
  //    return;
  //  }

  m_desiredRows = newDesiredRows;
  m_desiredColumns = ui->columnSpinBox->value();

  this->reload();
}

void GridPattern::setBestRowColumn() {
  QStringList newImagePathList;
  for (int i = 0; i < m_loadedImagePaths.count(); ++i) {
    auto a = m_loadedImagePaths.at(i);
    if (a.trimmed().isEmpty() == false) {
      newImagePathList.append(a);
    }
  }
  this->addPixmapItemsToView(newImagePathList);
  this->apply();
}

void GridPattern::swapRowColumn() {
  int rows = ui->rowsSpinBox->value();
  int columns = ui->columnSpinBox->value();

  m_desiredColumns = rows;
  m_desiredRows = columns;

  updateRowsColsSielently(columns, rows);

  this->reload();
}
