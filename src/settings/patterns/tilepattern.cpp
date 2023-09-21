#include "tilepattern.h"
#include "ui_tilepattern.h"

#include <QDebug>

TilePattern::TilePattern(QWidget *parent)
    : PatternBase(parent), ui(new Ui::TilePattern) {
  ui->setupUi(this);
}

TilePattern::~TilePattern() { delete ui; }

void TilePattern::apply() { qDebug() << "Applying a TilePattern."; }

void TilePattern::showCommonWidgets() {}

void TilePattern::reload() {}

void TilePattern::addPixmapItemsToView(const QStringList &imagePaths) {}

void TilePattern::prepare()
{

}
