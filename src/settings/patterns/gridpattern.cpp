#include "gridpattern.h"
#include "ui_gridpattern.h"

#include <QBrush>
#include <QDebug>
#include <imagewidgetitem.h>

GridPattern::GridPattern(GraphicsViewWidget *graphicsViewWidget,
                         LayoutWidget *layoutWidget, QWidget *parent)
    : PatternBase(parent), ui(new Ui::GridPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget) {

  ui->setupUi(this);

  ui->borderColorIndicator->setFixedSize(ui->selectBorderColorPb->height(),
                                         ui->selectBorderColorPb->height());

  ui->rowsSpinBox->setMinimum(1);
  ui->columnSpinBox->setMinimum(1);

  //========== START UI CONNECTIONS ====================
  connect(ui->spaceingSlider, &QSlider::valueChanged, this,
          &GridPattern::setSpacing);

  connect(ui->borderWidthSlider, &QSlider::valueChanged, this,
          &GridPattern::setBorderWidth);

  connect(ui->rowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setRowCount);

  connect(ui->columnSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          &GridPattern::setcolumnCount);

  connect(ui->selectBorderColorPb, &QPushButton::clicked, this,
          &GridPattern::chooseBorderColor);

  //========== END UI CONNECTIONS ====================
}

GridPattern::~GridPattern() { delete ui; }

//================START LAYOUT======================

void GridPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutProperties();
}

//================END LAYOUT======================

void GridPattern::setSpacing(int newValue) {
  m_desiredSpacing = newValue;
  this->reload();
}

void GridPattern::setBorderWidth(int newValue) {
  m_desiredBorderWidth = newValue;
  this->reload();
}

void GridPattern::setRowCount(int newRowCount) {
  int columnsCount = ui->columnSpinBox->value();

  if (newRowCount * columnsCount < m_loadedImagePaths.count()) {
    return;
  }

  m_desiredRows = newRowCount;
  m_desiredColumns = ui->columnSpinBox->value();

  addPixmapItemsToView(m_loadedImagePaths);
  this->reload();
}

void GridPattern::setcolumnCount(int newCoulmnCount) {

  int rowsCount = ui->rowsSpinBox->value();

  if (newCoulmnCount * rowsCount < m_loadedImagePaths.count()) {
    return;
  }

  m_desiredRows = ui->rowsSpinBox->value();
  m_desiredColumns = newCoulmnCount;

  addPixmapItemsToView(m_loadedImagePaths);
  this->reload();
}

void GridPattern::chooseBorderColor() {
  ColorChooserWidget colorChooser;
  QColor selectedColor = colorChooser.chooseColor(m_desiredBorderColor);
  if (selectedColor.isValid()) {
    this->updateBorderColorIndicatorColor(selectedColor);
    this->applyBorderColor(selectedColor);
  }
}

void GridPattern::updateBorderColorIndicatorColor(const QColor &color) {
  QString rgbaString = color.name(QColor::HexArgb);
  ui->borderColorIndicator->setStyleSheet(
      QString("background-color:%1;").arg(rgbaString));
}

void GridPattern::applyBorderColor(const QColor &color) {
  m_desiredBorderColor = color;
  this->reload();
}

void GridPattern::applyBackgroundProperties() {
  p_layoutWidget->applyBackgroundSettings();
}

void GridPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
}

void GridPattern::reload() { this->addPixmapItemsToView(m_loadedImagePaths); }

void GridPattern::apply() {

  this->applyLayoutProperties();

  this->applyBackgroundProperties();
}

void GridPattern::addPixmapItemsToView(const QStringList &imagePaths) {

  // required to block unnecessary empty requets
  if (imagePaths.empty())
    return;

  p_graphicsViewWidget->scene()->clear();

  if (imagePaths.isEmpty() == false) {
    m_loadedImagePaths = imagePaths;
  }

  const int numImages = m_loadedImagePaths.count();

  // GRID LAYOUT SPECIFIC
  QList<QPair<int, int>> gridVariants =
      GridUtils::findGridCombinations(numImages);

  if (gridVariants.isEmpty() == false) {
    QPair<int, int> bestGrid = gridVariants.first();

    int rowCount = m_desiredRows == 0 ? bestGrid.first : m_desiredRows;
    int columnCount =
        m_desiredColumns == 0 ? bestGrid.second : m_desiredColumns;

    GridUtils::GridInfo gridInfo = GridUtils::calculateCellSizeForItemCount(
        p_graphicsViewWidget->sceneRect().size(), numImages, m_desiredSpacing,
        rowCount, columnCount, m_desiredBorderWidth);

    this->updateRowsCols(gridInfo.rows, gridInfo.columns);

    for (int i = 0; i < numImages; ++i) {
      addPixmapItem(m_loadedImagePaths.at(i),
                    gridInfo.itemPositions.at(i).toPoint(), gridInfo.cellSize);
    }
  }
}

void GridPattern::addPixmapItem(const QString &imageFilePath, QPointF position,
                                QSizeF imageWidgetSize) {

  qreal devicePixelRatio = QGuiApplication::primaryScreen()->devicePixelRatio();

  QPixmap pixmap(imageFilePath);

  pixmap.setDevicePixelRatio(devicePixelRatio);

  pixmap =
      pixmap.scaled(QSize(imageWidgetSize.toSize()),
                    Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

  ImageWidgetItem *imageWidgetItem =
      new ImageWidgetItem(pixmap, m_desiredBorderColor, m_desiredBorderWidth);
  imageWidgetItem->setMaximumSize(imageWidgetSize);
  imageWidgetItem->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  imageWidgetItem->setPos(position);

  imageWidgetItem->setFlags(QGraphicsItem::ItemSendsScenePositionChanges);

  p_graphicsViewWidget->scene()->addItem(imageWidgetItem);
}

void GridPattern::prepare() {
  m_desiredRows = 0;
  m_desiredColumns = 0;
}

void GridPattern::updateRowsCols(int rowCount, int columnCount) {
  ui->rowsSpinBox->blockSignals(true);
  ui->rowsSpinBox->setValue(rowCount);
  ui->rowsSpinBox->blockSignals(false);

  ui->columnSpinBox->blockSignals(true);
  ui->columnSpinBox->setValue(columnCount);
  ui->columnSpinBox->blockSignals(false);
}
