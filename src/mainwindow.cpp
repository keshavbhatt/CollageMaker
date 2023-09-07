#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setWindowTitle(Utils::toCamelCase(qApp->applicationName()));

  m_sideBarWidget = new SideBarWidget(this);
  m_centerWidget = new CenterWidget(this);

  m_mainSplitter = new QSplitter(this);
  m_mainSplitter->setOrientation(Qt::Horizontal);
  m_mainSplitter->addWidget(m_sideBarWidget);
  m_mainSplitter->addWidget(m_centerWidget);
  m_mainSplitter->setCollapsible(1, false);

  ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);

  ui->centralwidget->layout()->addWidget(m_mainSplitter);
}

MainWindow::~MainWindow() { delete ui; }
