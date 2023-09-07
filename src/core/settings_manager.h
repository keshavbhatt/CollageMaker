#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include "settings_constants.h"
#include <QSettings>

using namespace SettingsConstants;
/**
 * @brief The SettingsManager singleton class
 */
class SettingsManager {
public:
  static SettingsManager &instance() {
    static SettingsManager instance;
    return instance;
  }

  QSettings &settings() { return m_settings; }

private:
  SettingsManager() {}

  QSettings m_settings;
};

#endif // SETTINGS_MANAGER_H
