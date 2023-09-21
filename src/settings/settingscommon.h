#ifndef SETTINGSCOMMON_H
#define SETTINGSCOMMON_H

#include <QSize>

class SettingsCommon {

public:
  enum class Orientation { Unset, Landscape, Portrait };
  static Orientation getOrientation(const QSize &size);

  enum Layouts { GridLayout, MosaicLayout, TileLayout };

  static bool isOrientationSet(const Orientation &orientation);
  SettingsCommon();
};

#endif // SETTINGSCOMMON_H
