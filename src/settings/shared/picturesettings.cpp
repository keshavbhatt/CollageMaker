#include "picturesettings.h"
#include "ui_picturesettings.h"

#include <colorchooserwidget.h>
#include <utils/commonutils.h>

PictureSettings::PictureSettings(GraphicsViewWidget *graphicsViewWidget,
                                 QWidget *parent)
    : QWidget(parent), ui(new Ui::PictureSettings),
      p_graphicsViewWidget(graphicsViewWidget) {
  ui->setupUi(this);

  //========== START UI CONNECTIONS ====================
  connect(ui->opacitySlider, &QSlider::valueChanged, this,
          &PictureSettings::setDesiredOpacity);

  connect(ui->cornerSlider, &QSlider::valueChanged, this,
          &PictureSettings::setDesiredBorderCornerSize);

  connect(ui->borderWidthSlider, &QSlider::valueChanged, this,
          &PictureSettings::setDesiredBorderWidth);

  connect(ui->selectBorderColorPb, &QPushButton::clicked, this,
          &PictureSettings::chooseBorderColor);
  //========== END UI CONNECTIONS ====================

  // border
  ui->borderWidthSlider->setRange(0, 100);
  ui->borderWidthSlider->setValue(1);
  ui->borderWidthSlider->setValue(0);

  // corner
  ui->cornerSlider->setRange(0, 999);
  ui->cornerSlider->setValue(1);
  ui->cornerSlider->setValue(0);

  // opacity
  ui->opacitySlider->setRange(0, 100);
  ui->opacitySlider->setValue(100);

  // color label
  updateBorderColorIndicatorColor(m_desiredBorderColor);
}

void PictureSettings::chooseBorderColor() {
  ColorChooserWidget colorChooser;
  QColor selectedColor = colorChooser.chooseColor(m_desiredBorderColor);
  if (selectedColor.isValid()) {
    this->updateBorderColorIndicatorColor(selectedColor);
    this->setDesiredBorderColor(selectedColor);
  }
}

qreal PictureSettings::desiredBorderCornerSize() const {
  return m_desiredBorderCornerSize;
}

void PictureSettings::updateBorderColorIndicatorColor(const QColor &color) {

  ui->borderColorIndicator->setFixedSize(ui->selectBorderColorPb->height(),
                                         ui->selectBorderColorPb->height());

  QString rgbaString = color.name(QColor::HexArgb);
  ui->borderColorIndicator->setStyleSheet(
      QString("border-radius: %1px; background-color:%2;")
          .arg(QString::number(ui->borderColorIndicator->height() / 2),
               rgbaString));
}

void PictureSettings::setDesiredBorderColor(
    const QColor &newDesiredBorderColor) {
  m_desiredBorderColor = newDesiredBorderColor;

  this->applySettings();
}

void PictureSettings::setDesiredOpacity(qreal newDesiredOpacity) {

  m_desiredOpacity = CommonUtils::sliderValueToReal(
      0.0, 1.0, ui->opacitySlider->maximum(), newDesiredOpacity);

  ui->opacityLabel->setText(QString::number(m_desiredOpacity, 'f', 2));

  this->applySettings();
}

void PictureSettings::setDesiredBorderWidth(qreal newDesiredBorderWidth) {

  m_desiredBorderWidth = CommonUtils::sliderValueToReal(
      0.0, 100.0, ui->borderWidthSlider->maximum(), newDesiredBorderWidth);

  ui->borderWidthLabel->setText(QString::number(m_desiredBorderWidth, 'f', 2));

  this->applySettings();
}

void PictureSettings::setDesiredBorderCornerSize(
    qreal newDesiredBorderCornerSize) {

  m_desiredBorderCornerSize = CommonUtils::sliderValueToReal(
      0.0, 200.0, ui->cornerSlider->maximum(), newDesiredBorderCornerSize);

  ui->cornerLabel->setText(QString::number(m_desiredBorderCornerSize, 'f', 2));

  this->applySettings();
}

qreal PictureSettings::desiredBorderWidth() const {
  return m_desiredBorderWidth;
}

QColor PictureSettings::desiredBorderColor() const {
  return m_desiredBorderColor;
}

void PictureSettings::applySettings() {

  QList<ImageWidgetItem *> imageWidgetItemsContainer =
      p_graphicsViewWidget->scene()->imageWidgetItemsContainer();

  if (!imageWidgetItemsContainer.isEmpty()) {

    qDebug() << "Picture Settings: applySettings()";

    const int numImages = imageWidgetItemsContainer.count();

    for (int i = 0; i < numImages; ++i) {
      ImageWidgetItem *imageItemWidget = imageWidgetItemsContainer.at(i);

      // opacity
      imageItemWidget->setOpacity(m_desiredOpacity);

      // corner
      imageItemWidget->setDesiredBorderCornerSize(m_desiredBorderCornerSize);

      // border
      imageItemWidget->setBorderColor(m_desiredBorderColor);
      imageItemWidget->setBorderWidth(m_desiredBorderWidth);
    }
  }
}

PictureSettings::~PictureSettings() { delete ui; }
