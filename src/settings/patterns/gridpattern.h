#ifndef GRIDPATTERN_H
#define GRIDPATTERN_H

#include "patternbase.h"

#include <QBrush>
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

private:
  Ui::GridPattern *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  void applyLayoutProperties();

  void applyBackgroundProperties();

  const QColor getBackgroundColor();
};

#endif // GRIDPATTERN_H
