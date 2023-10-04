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

#include <settings/shared/picturesettings.h>
#include <settings/shared/pictureshadowsettings.h>

namespace Ui {
class GridPattern;
}

class GridPattern : public PatternBase {
  Q_OBJECT

public:
  explicit GridPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                       LayoutWidget *layoutWidget = nullptr,
                       PictureSettings *pictureSettings = nullptr,
                         PictureShadowSettings *pictureShadowSettings = nullptr,
                       QWidget *parent = nullptr);
  ~GridPattern();

  void apply() override;

  void showCommonWidgets() override;

  void reload() override;

  void addPixmapItemsToView(const QStringList &imagePaths) override;

  void prepare() override;

  void setDesiredBorderColor(const QColor &newDesiredBorderColor);

  void setShadowEnabled(bool shadowEnabled);

private:
  Ui::GridPattern *ui;

  // spacing
  qreal m_desiredSpacing = 0.0;

  // row, cloumn
  int m_desiredRows = 0;
  int m_desiredColumns = 0;

  QStringList m_loadedImagePaths;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  PictureSettings *p_pictureSettings;

  PictureShadowSettings *p_pictureShadowSettings;

  bool m_customRowColumn;

  const QColor getBackgroundColor();

  void updateRowsColsSielently(int rowCount, int columnCount);

  void addPixmapItem(const QString &imageFilePath, QPointF position,
                     QSizeF imageWidgetSize);

  void updateBorderColorIndicatorColor(const QColor &color);

  void updateShadowColorIndicatorColor(const QColor &color);

  void updateLayoutPresetComboBox(QList<QPair<int, int>> gridVariants);

  void setLayoutPreset(int index);

  void swapRowColumn();

  void addAdditionalImageWidgetItems(const int additionalItemsCount);

  void applyLayoutProperties();

  void applyBackgroundProperties();

  void applyPictureProperties();

  void applyPictureShadowProperties();
private slots:
  void setDesiredSpacing(qreal newDesiredSpacing);

  void setDesiredColumns(int newDesiredColumns);

  void setDesiredRows(int newDesiredRows);

  void setBestRowColumn();
};

#endif // GRIDPATTERN_H
