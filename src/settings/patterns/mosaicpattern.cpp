#include "mosaicpattern.h"
#include "ui_mosaicpattern.h"

#include <QDebug>

MosaicPattern::MosaicPattern(GraphicsViewWidget *graphicsViewWidget,
                             LayoutWidget *layoutWidget, QWidget *parent)
    : PatternBase(parent), ui(new Ui::MosaicPattern),
      p_graphicsViewWidget(graphicsViewWidget), p_layoutWidget(layoutWidget) {
  ui->setupUi(this);

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
}

MosaicPattern::~MosaicPattern() { delete ui; }

//================START LAYOUT======================

void MosaicPattern::applyLayoutProperties() {

  p_layoutWidget->applyLayoutSettings();
}

//================END LAYOUT======================

void MosaicPattern::showCommonWidgets() {

  ui->layoutPlaceholder->addWidget(p_layoutWidget);
}

void MosaicPattern::apply() { this->applyLayoutProperties(); }
