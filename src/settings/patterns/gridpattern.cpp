#include "gridpattern.h"
#include "ui_gridpattern.h"

#include <QBrush>
#include <QDebug>

GridPattern::GridPattern(GraphicsViewWidget *graphicsViewWidget,
                         LayoutWidget *layoutWidget, QWidget *parent)
    : PatternBase(parent), ui(new Ui::GridPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget) {

  ui->setupUi(this);

  //========== START UI CONNECTIONS ====================


  //========== END UI CONNECTIONS ====================
}

GridPattern::~GridPattern() { delete ui; }

//================START LAYOUT======================

void GridPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutSettings();
}

//================END LAYOUT======================

void GridPattern::applyBackgroundProperties() {
  p_layoutWidget->applyBackgroundSettings();
}

void GridPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
}

void GridPattern::apply() {

  this->applyLayoutProperties();

  this->applyBackgroundProperties();
}
