#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

SideBarWidget::SideBarWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SideBarWidget) {
  ui->setupUi(this);

  m_libraryWidget = new LibraryWidget(this);

  ui->tabWidget->setCurrentWidget(ui->picturesTab);

  //----init each widget

  initPictureWidget();

  initSettingsWidget();

  initTextWidget();
}

void SideBarWidget::initPictureWidget() {
  ui->picturesTab->layout()->addWidget(m_libraryWidget);
}

void SideBarWidget::initSettingsWidget() { Q_UNIMPLEMENTED(); }

void SideBarWidget::initTextWidget() { Q_UNIMPLEMENTED(); }

SideBarWidget::~SideBarWidget() { delete ui; }
