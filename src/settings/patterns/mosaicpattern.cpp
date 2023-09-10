#include "mosaicpattern.h"
#include "ui_mosaicpattern.h"

#include <QDebug>

MosaicPattern::MosaicPattern(QWidget *parent)
    : PatternBase(parent), ui(new Ui::MosaicPattern) {
  ui->setupUi(this);
}

MosaicPattern::~MosaicPattern() { delete ui; }

void MosaicPattern::apply() { qDebug() << "Applying a MossaicPattern."; }
