#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

#include "pictures/librarywidget.h"

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QWidget {
  Q_OBJECT

public:
  explicit SideBarWidget(QWidget *parent = nullptr);
  ~SideBarWidget();

private:
  Ui::SideBarWidget *ui;
  LibraryWidget *m_libraryWidget;

  void initPictureWidget();
  void initSettingsWidget();
  void initTextWidget();
};

#endif // SIDEBARWIDGET_H
