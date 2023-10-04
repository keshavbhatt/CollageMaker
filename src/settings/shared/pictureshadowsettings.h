#ifndef PICTURESHADOWSETTINGS_H
#define PICTURESHADOWSETTINGS_H

#include <QWidget>
#include <graphicsviewwidget.h>

namespace Ui {
class PictureShadowSettings;
}

class PictureShadowSettings : public QWidget {
  Q_OBJECT

public:
  explicit PictureShadowSettings(
      GraphicsViewWidget *graphicsViewWidget = nullptr,
      QWidget *parent = nullptr);
  ~PictureShadowSettings();

  void applySettings();

  bool shadowEnabled() const;

private slots:
  void setDesiredShadowEffectColor(const QColor &newDesiredShadowEffectColor);
  void setDesiredShadowEffectBlurRadius(qreal newDesiredShadowEffectBlurRadius);
  void setDesiredShadowEffectOffsetY(qreal newDesiredShadowEffectOffsetY);
  void setDesiredShadowEffectOffsetX(qreal newDesiredShadowEffectOffsetX);
  void setShadowEnabled(bool shadowEnabled);

private:
  Ui::PictureShadowSettings *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  // shadow
  bool m_shadowEnabled = false;
  qreal m_desiredShadowEffectOffsetX = 0.0;
  qreal m_desiredShadowEffectOffsetY = 0.0;
  qreal m_desiredShadowEffectBlurRadius = 0;
  QColor m_desiredShadowEffectColor = QColor(63, 63, 63, 180);

  void updateShadowColorIndicatorColor(const QColor &color);
  void chooseShadowColor();
};

#endif // PICTURESHADOWSETTINGS_H
