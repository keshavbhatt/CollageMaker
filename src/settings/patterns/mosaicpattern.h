#ifndef MOSAICPATTERN_H
#define MOSAICPATTERN_H

#include "patternbase.h"

#include <QWidget>

namespace Ui {
class MosaicPattern;
}

class MosaicPattern : public PatternBase {
  Q_OBJECT

public:
  explicit MosaicPattern(QWidget *parent = nullptr);
  ~MosaicPattern();

private:
  Ui::MosaicPattern *ui;

  // PatternBase interface
public:
  void apply() override;

};

#endif // MOSAICPATTERN_H
