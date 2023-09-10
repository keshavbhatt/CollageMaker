#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

SideBarWidget::SideBarWidget(SettingsWidget *settingsWidget,
                             LibraryWidget *libraryWidget,
                             TextWidget *textWidget, QWidget *parent)
    : QWidget(parent), ui(new Ui::SideBarWidget),
      p_settingsWidget(settingsWidget), p_textWidget(textWidget),
      p_libraryWidget(libraryWidget) {
  ui->setupUi(this);

  ui->tabWidget->setCurrentWidget(ui->picturesTab);

  //----init each widget

  ui->settingsTab->layout()->addWidget(p_settingsWidget);

  ui->textTab->layout()->addWidget(p_textWidget);

  ui->picturesTab->layout()->addWidget(p_libraryWidget);

}


SideBarWidget::~SideBarWidget() { delete ui; }

LibraryWidget *SideBarWidget::libraryWidget() const { return p_libraryWidget; }
