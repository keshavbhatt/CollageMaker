#include "gridpattern.h"
#include "ui_gridpattern.h"

#include <QBrush>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <imagewidgetitem.h>

#include <utils/gridutils.h>

GridPattern::GridPattern(GraphicsViewWidget *graphicsViewWidget,
                         LayoutWidget *layoutWidget, QWidget *parent)
    : PatternBase(parent), ui(new Ui::GridPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget) {

  ui->setupUi(this);

  ui->borderColorIndicator->setFixedSize(ui->selectBorderColorPb->height(),
                                         ui->selectBorderColorPb->height());

  ui->rowsSpinBox->setMinimum(1);
  ui->columnSpinBox->setMinimum(1);

  ui->shadowEffectBlurRadiusSlider->setRange(0, 10);
  ui->shadowEffectOffsetXSlider->setRange(0, 10);
  ui->shadowEffectOffsetYSlider->setRange(0, 10);

  ui->cornerSlider->setRange(0, 100);

  updateBorderColorIndicatorColor(m_desiredBorderColor);

  //========== START UI CONNECTIONS ====================
  connect(ui->spaceingSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredSpacing);

  connect(ui->borderWidthSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredBorderWidth);

  connect(ui->rowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setDesiredRows);

  connect(ui->columnSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setDesiredColumns);

  connect(ui->selectBorderColorPb, &QPushButton::clicked, this,
          &GridPattern::chooseBorderColor);

  connect(ui->layoutPresetsComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &GridPattern::setLayoutPreset);

  connect(ui->shadowEffectOffsetXSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredShadowEffectOffsetX);

  connect(ui->shadowEffectOffsetYSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredShadowEffectOffsetY);

  connect(ui->shadowEffectBlurRadiusSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredShadowEffectBlurRadius);

  connect(ui->enableShadow, &QCheckBox::toggled, this,
          &GridPattern::setShadowEnabled);

  connect(ui->cornerSlider, &QSlider::valueChanged, this,
          &GridPattern::setDesiredBorderCornerSize);

  //========== END UI CONNECTIONS ====================
}

GridPattern::~GridPattern() { delete ui; }

//================START LAYOUT======================

void GridPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutProperties();
}

//================END LAYOUT======================

void GridPattern::chooseBorderColor() {
  ColorChooserWidget colorChooser;
  QColor selectedColor = colorChooser.chooseColor(m_desiredBorderColor);
  if (selectedColor.isValid()) {
    this->updateBorderColorIndicatorColor(selectedColor);
    this->setDesiredBorderColor(selectedColor);
  }
}

void GridPattern::updateBorderColorIndicatorColor(const QColor &color) {
  QString rgbaString = color.name(QColor::HexArgb);
  ui->borderColorIndicator->setStyleSheet(
      QString("background-color:%1;").arg(rgbaString));
}

void GridPattern::applyBackgroundProperties() {
  p_layoutWidget->applyBackgroundSettings();
}

void GridPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
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

void GridPattern::reload() {

  qDebug() << "Reload called";

  QList<ImageWidgetItem *> imageWidgetItemsContainer =
      p_graphicsViewWidget->scene()->imageWidgetItemsContainer();

  if (!imageWidgetItemsContainer.isEmpty()) {

    const int numImages = imageWidgetItemsContainer.count();

    // GRID LAYOUT SPECIFIC
    int rowCount = m_desiredRows;
    int columnCount = m_desiredColumns;

    GridUtils::GridInfo gridInfo = GridUtils::calculateCellSizeForItemCount(
        p_graphicsViewWidget->sceneRect().size(), numImages, m_desiredSpacing,
        rowCount, columnCount, m_desiredBorderWidth/*,
        m_desiredShadowEffectOffsetX, m_desiredShadowEffectOffsetY*/);

    this->updateRowsColsSielently(gridInfo.rows, gridInfo.columns);

    for (int i = 0; i < numImages; ++i) {
      ImageWidgetItem *imageItemWidget = imageWidgetItemsContainer.at(i);

      // position
      imageItemWidget->setPos(gridInfo.itemPositions.at(i).toPoint());

      // size
      imageItemWidget->setMinimumSize(gridInfo.cellSize.toSize());
      imageItemWidget->setMaximumSize(gridInfo.cellSize.toSize());

      // border
      imageItemWidget->setBorderColor(m_desiredBorderColor);
      imageItemWidget->setBorderWidth(m_desiredBorderWidth);

      // corner
      imageItemWidget->setDesiredBorderCornerSize(m_desiredBorderCornerSize);

      // shadow
      imageItemWidget->toggleShadowEffect(m_shadowEnabled);
      imageItemWidget->setDesiredShadowEffectOffsetX(
          m_desiredShadowEffectOffsetX);
      imageItemWidget->setDesiredShadowEffectOffsetY(
          m_desiredShadowEffectOffsetY);
      imageItemWidget->setDesiredShadowEffectBlurRadius(
          m_desiredShadowEffectBlurRadius);
      imageItemWidget->setDesiredShadowEffectColor(m_desiredShadowEffectColor);

      // pixmap item
      imageItemWidget->reload();
    }
  }
}

void GridPattern::apply() {

  this->applyLayoutProperties();

  this->applyBackgroundProperties();
}

void GridPattern::addPixmapItemsToView(const QStringList &imagePaths) {

  // required to block unnecessary empty requets
  if (imagePaths.empty())
    return;

  p_graphicsViewWidget->scene()->clearItemWidgets();

  if (imagePaths.isEmpty() == false) {
    m_loadedImagePaths = imagePaths;
  }

  const int numImages = m_loadedImagePaths.count();

  // GRID LAYOUT SPECIFIC
  QList<QPair<int, int>> gridVariants =
      GridUtils::findGridCombinations(numImages);

  if (gridVariants.isEmpty() == false) {
    updateLayoutPresetComboBox(gridVariants);

    QPair<int, int> bestGrid = gridVariants.first();

    int rowCount = m_desiredRows == 0 ? bestGrid.first : m_desiredRows;
    int columnCount =
        m_desiredColumns == 0 ? bestGrid.second : m_desiredColumns;

    GridUtils::GridInfo gridInfo = GridUtils::calculateCellSizeForItemCount(
        p_graphicsViewWidget->sceneRect().size(), numImages, m_desiredSpacing,
        rowCount, columnCount, m_desiredBorderWidth/*,
        m_desiredShadowEffectOffsetX, m_desiredShadowEffectOffsetY*/);

    this->updateRowsColsSielently(gridInfo.rows, gridInfo.columns);

    for (int i = 0; i < numImages; ++i) {
      addPixmapItem(m_loadedImagePaths.at(i),
                    gridInfo.itemPositions.at(i).toPoint(), gridInfo.cellSize);
    }
  }
}

void GridPattern::addPixmapItem(const QString &imageFilePath, QPointF position,
                                QSizeF imageWidgetSize) {
  ImageWidgetItem *imageWidgetItem =
      new ImageWidgetItem(imageFilePath, imageWidgetSize.toSize(),
                          m_desiredBorderColor, m_desiredBorderWidth);

  imageWidgetItem->setMinimumSize(imageWidgetSize);
  imageWidgetItem->setMaximumSize(imageWidgetSize);

  imageWidgetItem->setPos(position);
  imageWidgetItem->setFlags(QGraphicsItem::ItemSendsScenePositionChanges);

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
  }
  this->reload();
}

void GridPattern::setDesiredBorderColor(const QColor &newDesiredBorderColor) {
  m_desiredBorderColor = newDesiredBorderColor;

  this->reload();
}

void GridPattern::setShadowEnabled(bool shadowEnabled) {
  m_shadowEnabled = shadowEnabled;

  this->reload();
}

void GridPattern::setDesiredBorderCornerSize(qreal newDesiredBorderCornerSize) {
  m_desiredBorderCornerSize = newDesiredBorderCornerSize;
  ui->cornerLabel->setText(QString::number(m_desiredBorderCornerSize));

  this->reload();
}

void GridPattern::setDesiredSpacing(qreal newDesiredSpacing) {

  m_desiredSpacing = newDesiredSpacing;
  ui->spaceingLabel->setText(QString::number(m_desiredSpacing));

  this->reload();
}

void GridPattern::setDesiredBorderWidth(qreal newDesiredBorderWidth) {

  m_desiredBorderWidth = newDesiredBorderWidth;
  ui->borderWidthLabel->setText(QString::number(m_desiredBorderWidth));

  this->reload();
}

void GridPattern::setDesiredColumns(int newDesiredColumns) {

  int rowsCount = ui->rowsSpinBox->value();

  if (newDesiredColumns * rowsCount < m_loadedImagePaths.count()) {
    return;
  }

  m_desiredRows = ui->rowsSpinBox->value();
  m_desiredColumns = newDesiredColumns;

  this->reload();
}

void GridPattern::setDesiredRows(int newDesiredRows) {

  int columnsCount = ui->columnSpinBox->value();

  if (newDesiredRows * columnsCount < m_loadedImagePaths.count()) {
    return;
  }

  m_desiredRows = newDesiredRows;
  m_desiredColumns = ui->columnSpinBox->value();

  this->reload();
}

void GridPattern::setDesiredShadowEffectOffsetX(
    qreal newDesiredShadowEffectOffsetX) {

  m_desiredShadowEffectOffsetX = newDesiredShadowEffectOffsetX;

  ui->shadowEffectOffsetXLabel->setText(
      QString::number(m_desiredShadowEffectOffsetX));

  this->reload();
}

void GridPattern::setDesiredShadowEffectOffsetY(
    qreal newDesiredShadowEffectOffsetY) {
  m_desiredShadowEffectOffsetY = newDesiredShadowEffectOffsetY;

  ui->shadowEffectOffsetYLabel->setText(
      QString::number(m_desiredShadowEffectOffsetY));

  this->reload();
}

void GridPattern::setDesiredShadowEffectBlurRadius(
    qreal newDesiredShadowEffectBlurRadius) {

  m_desiredShadowEffectBlurRadius = newDesiredShadowEffectBlurRadius;

  ui->shadowEffectBlurRadiusLabel->setText(
      QString::number(m_desiredShadowEffectBlurRadius));

  this->reload();
}

void GridPattern::setDesiredShadowEffectColor(
    const QColor &newDesiredShadowEffectColor) {

  m_desiredShadowEffectColor = newDesiredShadowEffectColor;

  this->reload();
}
