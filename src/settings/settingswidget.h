#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "graphicsviewwidget.h"
#include "patterns/gridpattern.h"
#include "patterns/mosaicpattern.h"
#include "patterns/tilepattern.h"

#include <QWidget>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

public:
  explicit SettingsWidget(GraphicsViewWidget *graphicsViewWidget = nullptr,
                          QWidget *parent = nullptr);
  ~SettingsWidget();

  QString getPatternWidgetObjectNameByPatternName(const QString &patternName);

private:
  Ui::SettingsWidget *ui;
  QStringList m_supportedPatterns;

  GraphicsViewWidget *p_graphicsViewWidget;

  void initPatternOptionWidget();

  void initGridPattern();
  void initMosaicPattern();
  void initTilePatterm();

  QWidget *getPatternWidgetByPatternName(const QString &patternName);

private slots:
  void switchPatternWidget(int index);
};

#endif // SETTINGSWIDGET_H
