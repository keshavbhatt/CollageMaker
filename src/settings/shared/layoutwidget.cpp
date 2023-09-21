#include "layoutwidget.h"
#include "ui_layoutwidget.h"

#include <QFileDialog>
#include <colorchooserwidget.h>

#include <core/medialoader.h>

LayoutWidget::LayoutWidget(GraphicsViewWidget *graphicsViewWidget,
                           QWidget *parent)
    : QWidget(parent), ui(new Ui::LayoutWidget),
      p_graphicsViewWidget(graphicsViewWidget),
      m_resolutionModel(new ResolutionModel) {

  ui->setupUi(this);

  ui->bgColorIndicator->setFixedSize(ui->backgroundColorPb->height(),
                                     ui->backgroundColorPb->height());

  ui->resolutionComboBox->setModel(m_resolutionModel);
  ui->resolutionComboBox->setCurrentIndex(3);

  ui->tileScaleFactorSpinBox->setRange(0.01, 10.0);
  ui->tileScaleFactorSpinBox->setValue(
      p_graphicsViewWidget->scene()->tiledBgScaleFactor());
  ui->tileScaleFactorSpinBox->setStepType(
      QAbstractSpinBox::AdaptiveDecimalStepType);

  m_orientationButtonGroup = new QButtonGroup(this);
  m_orientationButtonGroup->addButton(ui->landscapeRadioBtn);
  m_orientationButtonGroup->addButton(ui->portraitRadioBtn);
  connect(m_orientationButtonGroup,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          &LayoutWidget::handleOrientationButtonPress);

  //========== START UI CONNECTIONS ====================

  connect(
      ui->resolutionComboBox,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, &LayoutWidget::applyResolution);

  connect(ui->backgroundColorPb, &QPushButton::clicked, this,
          &LayoutWidget::chooseBackgroundColor);

  connect(ui->backgroundImagePb, &QPushButton::clicked, this,
          &LayoutWidget::chooseBackgroundImage);

  connect(ui->transparentBgCheckBox, &QCheckBox::toggled, this,
          &LayoutWidget::setTransparentBackground);

  connect(ui->tiledBgCheckBox, &QCheckBox::toggled, this,
          &LayoutWidget::setTiledBackground);

  connect(ui->tileScaleFactorSpinBox,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &LayoutWidget::updateTilesScaleFactor);

  connect(ui->resetTileScaleFactorPb, &QPushButton::clicked, this,
          &LayoutWidget::resetTilesScaleFactor);

  //========== END UI CONNECTIONS ====================
}

void LayoutWidget::handleOrientation(
    const SettingsCommon::Orientation &orientation) {

  ResolutionModel::ResolutionItem selectedResolution =
      m_resolutionModel->resolution(ui->resolutionComboBox->currentIndex());

  QSize currentSize = selectedResolution.size;

  switch (orientation) {
  case SettingsCommon::Orientation::Landscape:
    if (currentSize.width() > currentSize.height()) {
      // The current size is already landscape
      this->viewSetCustomSize(currentSize);
    } else {
      // Calculate the landscape size by swapping width and height
      QSize landscapeSize = currentSize;
      landscapeSize.transpose(); // Swap width and height
      this->viewSetCustomSize(landscapeSize);
    }
    break;
  case SettingsCommon::Orientation::Portrait:
    if (currentSize.height() > currentSize.width()) {
      // The current size is already portrait
      this->viewSetCustomSize(currentSize);
    } else {
      // Calculate the portrait size by swapping width and height
      QSize portraitSize = currentSize;
      portraitSize.transpose(); // Swap width and height
      this->viewSetCustomSize(portraitSize);
    }
    break;
  default:
    // do nothing
    break;
  }
}

void LayoutWidget::viewSetCustomSize(QSize size){
  p_graphicsViewWidget->viewSetCustomSize(size);
  p_graphicsViewWidget->currentPattern()->reload();
}

void LayoutWidget::handleOrientationButtonPress(QAbstractButton *button) {
  if (button == ui->landscapeRadioBtn) {
    handleOrientation(SettingsCommon::Orientation::Landscape);
    m_currentOrientation = SettingsCommon::Orientation::Landscape;
  } else if (button == ui->portraitRadioBtn) {
    handleOrientation(SettingsCommon::Orientation::Portrait);
    m_currentOrientation = SettingsCommon::Orientation::Portrait;
  }
}

void LayoutWidget::switchOrientation(
    const SettingsCommon::Orientation &orientation) {

  switch (orientation) {
  case SettingsCommon::Orientation::Landscape:
    ui->landscapeRadioBtn->setChecked(true);
    break;
  case SettingsCommon::Orientation::Portrait:
    ui->portraitRadioBtn->setChecked(true);
    break;
  default:
    ui->landscapeRadioBtn->setChecked(true);
    break;
  }

  handleOrientation(orientation);
}

void LayoutWidget::applyResolution(int resolutionIndex) {

  // resolution
  ResolutionModel::ResolutionItem selectedResolution =
      m_resolutionModel->resolution(resolutionIndex);

  this->viewSetCustomSize(selectedResolution.size);

  // select correct Orientation if it is not already set by user
  if (SettingsCommon::isOrientationSet(m_currentOrientation)) {
    switchOrientation(m_currentOrientation);
  } else {
    SettingsCommon::Orientation orientation =
        SettingsCommon::getOrientation(selectedResolution.size);

    switchOrientation(orientation);
  }
}

//================START BACKGROUND======================

const QColor LayoutWidget::getCurrentBackgroundColor() {
  return p_graphicsViewWidget->scene()->getBackgroundColor();
}

void LayoutWidget::chooseBackgroundColor() {
  ColorChooserWidget colorChooser;
  QColor selectedColor = colorChooser.chooseColor(getCurrentBackgroundColor());
  if (selectedColor.isValid()) {
    this->updateBgColorIndicatorColor(selectedColor);
    this->applyBackgroundColor(selectedColor);
  }
}

void LayoutWidget::chooseBackgroundImage() {
  QString selectedImageFileUrl =
      MediaLoader::getInstance().getSelectedImageFileUrl();
  if (selectedImageFileUrl.isEmpty() == false) {
    p_graphicsViewWidget->scene()->setBackgroundImage(selectedImageFileUrl);
  }
}

void LayoutWidget::setTransparentBackground(bool transparent) {
  if (transparent) {
    p_graphicsViewWidget->scene()->setTransparentBackground();
  } else {
    QColor color = getCurrentBackgroundColor();
    p_graphicsViewWidget->scene()->setBackgroundColor(color);
  }
}

void LayoutWidget::setTiledBackground(const bool &tiled) {
  p_graphicsViewWidget->scene()->setBackgroundImageTiled(tiled);
  updateTilesScaleFactor(p_graphicsViewWidget->scene()->tiledBgScaleFactor());
}

void LayoutWidget::updateTilesScaleFactor(const double &scaleFactor) {
  p_graphicsViewWidget->scene()->setTiledBgScaleFactor(scaleFactor);
}

void LayoutWidget::resetTilesScaleFactor() {
  p_graphicsViewWidget->scene()->resetTiledBgScaleFactor();
  ui->tileScaleFactorSpinBox->setValue(
      p_graphicsViewWidget->scene()->tiledBgScaleFactor());
}

void LayoutWidget::updateBgColorIndicatorColor(const QColor &color) {
  QString rgbaString = color.name(QColor::HexArgb);
  ui->bgColorIndicator->setStyleSheet(
      QString("background-color:%1;").arg(rgbaString));
}

void LayoutWidget::applyBackgroundColor(const QColor &color) {
  // background
  p_graphicsViewWidget->scene()->setBackgroundColor(color);
}

//================END BACKGROUND======================

LayoutWidget::~LayoutWidget() { delete ui; }

void LayoutWidget::applyLayoutProperties() {

  this->applyResolution(ui->resolutionComboBox->currentIndex());

}

void LayoutWidget::applyBackgroundSettings() {
  if (!getCurrentBackgroundColor().isValid()) {

    QColor defaultColor = Qt::gray;

    this->updateBgColorIndicatorColor(defaultColor);

    this->applyBackgroundColor(defaultColor); // default bg color

    this->setTransparentBackground(ui->transparentBgCheckBox->isChecked());
  }
}
