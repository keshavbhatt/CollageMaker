#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include "../resolutionmodel.h"
#include "settings/settingscommon.h"
#include <QButtonGroup>
#include <QWidget>
#include <graphicsviewwidget.h>

namespace Ui {
class LayoutWidget;
}

class LayoutWidget : public QWidget {
  Q_OBJECT

public:
  explicit LayoutWidget(GraphicsViewWidget *graphicsViewWidget = nullptr,
                        QWidget *parent = nullptr);
  ~LayoutWidget();

  void applyLayoutProperties();

  void applyBackgroundSettings();

signals:
  void propertyChanged();

private slots:
  void handleOrientationButtonPress(QAbstractButton *button);
  void applyResolution(int resolutionIndex);
  void setTransparentBackground(bool transparent);
  void chooseBackgroundColor();
  void chooseBackgroundImage();
  void setTiledBackground(const bool &tiled);
  void resetTilesScaleFactor();
  void updateTilesScaleFactor(const double &scaleFactor);

  void setBgPictureBlurRadiusSlider(const int &value);
  private:
  Ui::LayoutWidget *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  ResolutionModel *m_resolutionModel;

  QButtonGroup *m_orientationButtonGroup;

  SettingsCommon::Orientation m_currentOrientation =
      SettingsCommon::Orientation::Unset;

  void handleOrientation(const SettingsCommon::Orientation &orientation);
  void switchOrientation(const SettingsCommon::Orientation &orientation);
  void applyBackgroundColor(const QColor &color);
  void updateBgColorIndicatorColor(const QColor &color);
  const QColor getCurrentBackgroundColor();
  void viewSetCustomSize(QSize size);
};

#endif // LAYOUTWIDGET_H
