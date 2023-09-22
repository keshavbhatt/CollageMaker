#ifndef GRIDPATTERN_H
#define GRIDPATTERN_H

#include "patternbase.h"

#include <QBrush>
#include <QColor>
#include <QScreen>
#include <QWidget>

#include "colorchooserwidget.h"
#include "graphicsviewwidget.h"
#include "settings/shared/layoutwidget.h"

namespace Ui {
class GridPattern;
}

class GridPattern : public PatternBase {
  Q_OBJECT

public:
  explicit GridPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                       LayoutWidget *layoutWidget = nullptr,
                       QWidget *parent = nullptr);
  ~GridPattern();

  void apply() override;

  void showCommonWidgets() override;

  void reload() override;

  void addPixmapItemsToView(const QStringList &imagePaths) override;

  void prepare() override;

  void setDesiredBorderColor(const QColor &newDesiredBorderColor);

  void setShadowEnabled(bool shadowEnabled);

  private:
  Ui::GridPattern *ui;

  qreal m_desiredSpacing = 0.0;

  int m_desiredRows = 0;

  int m_desiredColumns = 0;

  qreal m_desiredBorderWidth = 0.0;
  QColor m_desiredBorderColor = Qt::white;

  bool m_shadowEnabled = false;
  qreal m_desiredShadowEffectOffsetX = 0.0;
  qreal m_desiredShadowEffectOffsetY = 0.0;
  qreal m_desiredShadowEffectBlurRadius = 0;
  QColor m_desiredShadowEffectColor = QColor(63, 63, 63, 180);

  QStringList m_loadedImagePaths;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  void applyLayoutProperties();

  void applyBackgroundProperties();

  const QColor getBackgroundColor();

  void updateRowsColsSielently(int rowCount, int columnCount);

  void addPixmapItem(const QString &imageFilePath, QPointF position,
                     QSizeF imageWidgetSize);
  void updateBorderColorIndicatorColor(const QColor &color);
  void updateLayoutPresetComboBox(QList<QPair<int, int>> gridVariants);
  void setLayoutPreset(int index);

private slots:
  void chooseBorderColor();

  void setDesiredSpacing(qreal newDesiredSpacing);

  void setDesiredBorderWidth(qreal newDesiredBorderWidth);

  void setDesiredColumns(int newDesiredColumns);

  void setDesiredRows(int newDesiredRows);

  void setDesiredShadowEffectOffsetX(qreal newDesiredShadowEffectOffsetX);

  void setDesiredShadowEffectOffsetY(qreal newDesiredShadowEffectOffsetY);

  void setDesiredShadowEffectBlurRadius(qreal newDesiredShadowEffectBlurRadius);

  void setDesiredShadowEffectColor(const QColor &newDesiredShadowEffectColor);
};

#endif // GRIDPATTERN_H
