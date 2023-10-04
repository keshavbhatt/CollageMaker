#include "pictureshadowsettings.h"
#include "ui_pictureshadowsettings.h"

#include "colorchooserwidget.h"
#include "imagewidgetitem.h"
#include "utils/commonutils.h"

PictureShadowSettings::PictureShadowSettings(
    GraphicsViewWidget *graphicsViewWidget, QWidget *parent)
    : QWidget(parent), ui(new Ui::PictureShadowSettings),
      p_graphicsViewWidget(graphicsViewWidget) {
  ui->setupUi(this);

  connect(ui->shadowEffectOffsetXSlider, &QSlider::valueChanged, this,
          &PictureShadowSettings::setDesiredShadowEffectOffsetX);

  connect(ui->shadowEffectOffsetYSlider, &QSlider::valueChanged, this,
          &PictureShadowSettings::setDesiredShadowEffectOffsetY);

  connect(ui->shadowEffectBlurRadiusSlider, &QSlider::valueChanged, this,
          &PictureShadowSettings::setDesiredShadowEffectBlurRadius);

  connect(ui->enableShadow, &QCheckBox::toggled, this,
          &PictureShadowSettings::setShadowEnabled);

  connect(ui->selectShadowColorPb, &QPushButton::clicked, this,
          &PictureShadowSettings::chooseShadowColor);

  // shadow
  ui->shadowEffectBlurRadiusSlider->setRange(1, 100);
  ui->shadowEffectBlurRadiusSlider->setValue(1);

  ui->shadowEffectOffsetXSlider->setRange(0, 100);
  ui->shadowEffectOffsetXSlider->setValue(50);

  ui->shadowEffectOffsetYSlider->setRange(0, 100);
  ui->shadowEffectOffsetYSlider->setValue(50);

  // shadow Color label
  updateShadowColorIndicatorColor(m_desiredShadowEffectColor);
}

void PictureShadowSettings::setDesiredShadowEffectOffsetX(
    qreal newDesiredShadowEffectOffsetX) {

  m_desiredShadowEffectOffsetX = CommonUtils::sliderValueToReal(
      -20.0, 20.0, ui->shadowEffectOffsetXSlider->maximum(),
      newDesiredShadowEffectOffsetX);

  ui->shadowEffectOffsetXLabel->setText(
      QString::number(m_desiredShadowEffectOffsetX, 'f', 2));

  this->applySettings();
}

void PictureShadowSettings::setDesiredShadowEffectOffsetY(
    qreal newDesiredShadowEffectOffsetY) {

  m_desiredShadowEffectOffsetY = CommonUtils::sliderValueToReal(
      -20.0, 20.0, ui->shadowEffectOffsetYSlider->maximum(),
      newDesiredShadowEffectOffsetY);

  ui->shadowEffectOffsetYLabel->setText(
      QString::number(m_desiredShadowEffectOffsetY, 'f', 2));

  this->applySettings();
}

void PictureShadowSettings::setDesiredShadowEffectBlurRadius(
    qreal newDesiredShadowEffectBlurRadius) {

  m_desiredShadowEffectBlurRadius = CommonUtils::sliderValueToReal(
      0.0, 100.0, ui->shadowEffectBlurRadiusSlider->maximum(),
      newDesiredShadowEffectBlurRadius);

  ui->shadowEffectBlurRadiusLabel->setText(
      QString::number(m_desiredShadowEffectBlurRadius, 'f', 2));

  this->applySettings();
}

void PictureShadowSettings::setDesiredShadowEffectColor(
    const QColor &newDesiredShadowEffectColor) {

  m_desiredShadowEffectColor = newDesiredShadowEffectColor;

  this->applySettings();
}

void PictureShadowSettings::chooseShadowColor() {
  ColorChooserWidget colorChooser;
  QColor selectedColor = colorChooser.chooseColor(m_desiredShadowEffectColor);
  if (selectedColor.isValid()) {
    this->updateShadowColorIndicatorColor(selectedColor);
    this->setDesiredShadowEffectColor(selectedColor);
  }
}

void PictureShadowSettings::updateShadowColorIndicatorColor(
    const QColor &color) {

  ui->shadowColorIndicator->setFixedSize(ui->selectShadowColorPb->height(),
                                         ui->selectShadowColorPb->height());

  QString rgbaString = color.name(QColor::HexArgb);
  ui->shadowColorIndicator->setStyleSheet(
      QString("border-radius: %1px; background-color:%2;")
          .arg(QString::number(ui->shadowColorIndicator->height() / 2),
               rgbaString));
}

void PictureShadowSettings::setShadowEnabled(bool shadowEnabled) {
  m_shadowEnabled = shadowEnabled;

  this->applySettings();
}

bool PictureShadowSettings::shadowEnabled() const { return m_shadowEnabled; }

void PictureShadowSettings::applySettings() {
  QList<ImageWidgetItem *> imageWidgetItemsContainer =
      p_graphicsViewWidget->scene()->imageWidgetItemsContainer();

  if (!imageWidgetItemsContainer.isEmpty()) {

    qDebug() << "Picture Settings: applySettings()";

    const int numImages = imageWidgetItemsContainer.count();

    for (int i = 0; i < numImages; ++i) {
      ImageWidgetItem *imageItemWidget = imageWidgetItemsContainer.at(i);

      // shadow
      imageItemWidget->toggleShadowEffect(m_shadowEnabled);
      imageItemWidget->setDesiredShadowEffectOffsetX(
          m_desiredShadowEffectOffsetX);
      imageItemWidget->setDesiredShadowEffectOffsetY(
          m_desiredShadowEffectOffsetY);
      imageItemWidget->setDesiredShadowEffectBlurRadius(
          m_desiredShadowEffectBlurRadius);
      imageItemWidget->setDesiredShadowEffectColor(m_desiredShadowEffectColor);
    }
  }
}

PictureShadowSettings::~PictureShadowSettings() { delete ui; }
