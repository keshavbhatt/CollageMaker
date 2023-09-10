#ifndef GRIDPATTERN_H
#define GRIDPATTERN_H

#include "../resolutionmodel.h"
#include "patternbase.h"

#include <QWidget>
#include <graphicsviewwidget.h>

namespace Ui {
class GridPattern;
}

class GridPattern : public PatternBase {
  Q_OBJECT

public:
  explicit GridPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                       QWidget *parent = nullptr);
  ~GridPattern();

  void apply() override;

private:
  Ui::GridPattern *ui;
  GraphicsViewWidget *p_graphicsViewWidget;
  ResolutionModel *m_resolutionModel;
};

#endif // GRIDPATTERN_H
