#ifndef MOSAICPATTERN_H
#define MOSAICPATTERN_H

#include <QWidget>

#include "graphicsviewwidget.h"
#include "patternbase.h"
#include "settings/shared/layoutwidget.h"

namespace Ui {
class MosaicPattern;
}

class MosaicPattern : public PatternBase {
  Q_OBJECT

public:
  explicit MosaicPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                         LayoutWidget *layoutWidget = nullptr,
                         QWidget *parent = nullptr);
  ~MosaicPattern();

private:
  Ui::MosaicPattern *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  void applyLayoutProperties();

  // PatternBase interface
public:
  void apply() override;
  void showCommonWidgets() override;
};

#endif // MOSAICPATTERN_H
