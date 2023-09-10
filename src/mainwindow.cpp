#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setWindowTitle(Utils::toCamelCase(qApp->applicationName()));

  m_graphicsViewWidget = new GraphicsViewWidget();

  m_libraryWidget = new LibraryWidget(m_graphicsViewWidget);

  m_settingsWidget = new SettingsWidget(m_graphicsViewWidget);

  m_textWidget = new TextWidget(m_graphicsViewWidget);

  m_sideBarWidget =
      new SideBarWidget(m_settingsWidget, m_libraryWidget, m_textWidget, this);

  m_centerWidget = new CenterWidget(m_graphicsViewWidget, this);

  m_mainSplitter = new QSplitter(this);
  m_mainSplitter->setOrientation(Qt::Horizontal);
  m_mainSplitter->addWidget(m_sideBarWidget);
  m_mainSplitter->addWidget(m_centerWidget);
  m_mainSplitter->setStretchFactor(0, 1);
  m_mainSplitter->setStretchFactor(1, 2);
  m_mainSplitter->setChildrenCollapsible(false);

  ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

  ui->centralwidget->layout()->addWidget(m_mainSplitter);

}

MainWindow::~MainWindow() { delete ui; }
