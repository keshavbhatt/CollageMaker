#ifndef GRIDPATTERN_H
#define GRIDPATTERN_H

#include "patternbase.h"

#include <QBrush>
#include <QColor>
#include <QScreen>
#include <QWidget>

#include "colorchooserwidget.h"
#include "graphicsviewwidget.h"
#include "settings/shared/layoutwidget.h"

namespace Ui {
class GridPattern;
}

class GridPattern : public PatternBase {
  Q_OBJECT

public:
  explicit GridPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                       LayoutWidget *layoutWidget = nullptr,
                       QWidget *parent = nullptr);
  ~GridPattern();

  void apply() override;

  void showCommonWidgets() override;

  void reload() override;

  void addPixmapItemsToView(const QStringList &imagePaths) override;

  void prepare() override;

private:
  Ui::GridPattern *ui;

  qreal m_desiredSpacing = 0.0;

  int m_desiredRows = 0;

  int m_desiredColumns = 0;

  QColor m_desiredBorderColor = Qt::white;

  qreal m_desiredBorderWidth = 0.0;

  QStringList m_loadedImagePaths;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  void applyLayoutProperties();

  void applyBackgroundProperties();

  const QColor getBackgroundColor();

  void updateRowsCols(int rowCount, int columnCount);

  void addPixmapItem(const QString &imageFilePath, QPointF position,
                     QSizeF imageWidgetSize);
  void updateBorderColorIndicatorColor(const QColor &color);
  void applyBorderColor(const QColor &color);
  private slots:
  void setSpacing(int newValue);
  void setcolumnCount(int newCoulmnCount);
  void setRowCount(int newRowCount);
  void setBorderWidth(int newValue);
  void chooseBorderColor();
};

#endif // GRIDPATTERN_H
