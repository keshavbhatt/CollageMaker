#ifndef TILEPATTERN_H
#define TILEPATTERN_H

#include "patternbase.h"

#include <QWidget>

namespace Ui {
class TilePattern;
}

class TilePattern : public PatternBase {
  Q_OBJECT

public:
  explicit TilePattern(QWidget *parent = nullptr);
  ~TilePattern();

private:
  Ui::TilePattern *ui;

  // PatternBase interface
public:
  void apply() override;

  void showCommonWidgets() override;

  void reload() override;

  void addPixmapItemsToView(const QStringList &imagePaths) override;

  void prepare() override;
};

#endif // TILEPATTERN_H
