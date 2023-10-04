#ifndef MOSAICPATTERN_H
#define MOSAICPATTERN_H

#include <QWidget>

#include "graphicsviewwidget.h"
#include "patternbase.h"
#include "settings/shared/layoutwidget.h"
#include "settings/shared/pictureshadowsettings.h"
#include "utils/mosaicutils.h"
#include <settings/shared/picturesettings.h>

namespace Ui {
class MosaicPattern;
}

class MosaicPattern : public PatternBase {
  Q_OBJECT

public:
  explicit MosaicPattern(GraphicsViewWidget *graphicsViewWidget = nullptr,
                         LayoutWidget *layoutWidget = nullptr,
                         PictureSettings *pictureSettings = nullptr,
                         PictureShadowSettings *pictureShadowSettings = nullptr,
                         QWidget *parent = nullptr);
  ~MosaicPattern();

private:
  Ui::MosaicPattern *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  LayoutWidget *p_layoutWidget;

  void applyLayoutProperties();

  void applyBackgroundProperties();

  void applyPictureProperties();

  PictureSettings *p_pictureSettings;

  PictureShadowSettings *p_pictureShadowSettings;

public:
  void apply() override;

  void showCommonWidgets() override;

  void reload() override;

  void addPixmapItemsToView(const QStringList &imagePaths) override;

  void prepare() override;
};

#endif // MOSAICPATTERN_H
