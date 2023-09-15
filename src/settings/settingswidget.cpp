#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QDebug>

SettingsWidget::SettingsWidget(GraphicsViewWidget *graphicsViewWidget,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::SettingsWidget),
      p_graphicsViewWidget(graphicsViewWidget),
      m_layoutWidget(new LayoutWidget(p_graphicsViewWidget, this)) {

  ui->setupUi(this);

  m_supportedPatterns = (QStringList() << "Grid Pattern"
                                       << "Mosaic Pattern"
                                       /*<< "Tile Pattern"*/);

  ui->patternComboBox->addItems(m_supportedPatterns);

  initPatternOptionWidget();

  connect(ui->patternComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &SettingsWidget::switchPatternWidget);

  switchPatternWidget(ui->patternComboBox->currentIndex());
}

void SettingsWidget::initPatternOptionWidget() {
  foreach (QString patternName, m_supportedPatterns) {
    QString patternWidgetClassName =
        getPatternWidgetObjectNameByPatternName(patternName);

    if (patternWidgetClassName == "GridPattern") {
      PatternBase *gridPattern =
          new GridPattern(p_graphicsViewWidget, m_layoutWidget, this);
      gridPattern->setObjectName(patternWidgetClassName);
      ui->patternOptionWidget->addWidget(gridPattern);
    } else if (patternWidgetClassName == "MosaicPattern") {
      PatternBase *mosaicPattern =
          new MosaicPattern(p_graphicsViewWidget, m_layoutWidget, this);
      mosaicPattern->setObjectName(patternWidgetClassName);
      ui->patternOptionWidget->addWidget(mosaicPattern);
    } else if (patternWidgetClassName == "TilePattern") {
      PatternBase *tilePattern = new TilePattern(this);
      tilePattern->setObjectName(patternWidgetClassName);
      ui->patternOptionWidget->addWidget(tilePattern);
    }
  }
}

QString SettingsWidget::getPatternWidgetObjectNameByPatternName(
    const QString &patternName) {
  return QString(patternName).replace(" ", "");
}

PatternBase *
SettingsWidget::getPatternWidgetByPatternName(const QString &patternName) {
  QString targetWidgetObjectName =
      getPatternWidgetObjectNameByPatternName(patternName);
  return this->findChild<PatternBase *>(targetWidgetObjectName);
}

void SettingsWidget::switchPatternWidget(int index) {
  if (index <= m_supportedPatterns.size()) {
    QString patternName = m_supportedPatterns.at(index);

    auto patternWidget = getPatternWidgetByPatternName(patternName);
    if (patternWidget) {
      ui->patternOptionWidget->slideInWgt(patternWidget);
      patternWidget->showCommonWidgets();
      patternWidget->apply();
    } else {
      qDebug() << "Unable to switch, widget not found";
    }
  } else {
    qDebug() << "Unable to switch, index out of bound";
  }
}

SettingsWidget::~SettingsWidget() { delete ui; }
