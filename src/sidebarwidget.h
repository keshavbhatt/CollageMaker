#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

#include "pictures/librarywidget.h"
#include <settings/settingswidget.h>

#include <text/textwidget.h>

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QWidget {
  Q_OBJECT

public:
  explicit SideBarWidget(SettingsWidget *settingsWidget = nullptr,
                         LibraryWidget *libraryWidget = nullptr,
                         TextWidget *textWidget = nullptr,
                         QWidget *parent = nullptr);
  ~SideBarWidget();

  LibraryWidget *libraryWidget() const;

private:
  Ui::SideBarWidget *ui;

  SettingsWidget *p_settingsWidget;
  TextWidget *p_textWidget;
  LibraryWidget *p_libraryWidget;
};

#endif // SIDEBARWIDGET_H
