#include "settingscommon.h"

SettingsCommon::Orientation SettingsCommon::getOrientation(const QSize &size) {
  if (size.width() > size.height()) {
    return Orientation::Landscape;
  } else {
    return Orientation::Portrait;
  }
}

bool SettingsCommon::isOrientationSet(const Orientation &orientation) {
  return orientation != Orientation::Unset;
}

SettingsCommon::SettingsCommon() {}
