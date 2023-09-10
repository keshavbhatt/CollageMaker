#include "gridpattern.h"
#include "ui_gridpattern.h"

#include <QDebug>

GridPattern::GridPattern(GraphicsViewWidget *graphicsViewWidget,
                         QWidget *parent)
    : PatternBase(parent), ui(new Ui::GridPattern),
      p_graphicsViewWidget(graphicsViewWidget),
      m_resolutionModel(new ResolutionModel) {

  ui->setupUi(this);

  ui->resolutionComboBox->setModel(m_resolutionModel);

  // Connect the QComboBox's currentIndexChanged signal to update
  // QGraphicsView's resolution
  connect(
      ui->resolutionComboBox,
      static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
      this, [&](int index) {
        ResolutionModel::ResolutionItem selectedResolution =
            m_resolutionModel->resolution(index);
        p_graphicsViewWidget->setCustomSize(selectedResolution.size);
      });
}

GridPattern::~GridPattern() { delete ui; }

void GridPattern::apply() { qDebug() << "Applying a GridPattern."; }
