#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

#include "centerwidget.h"
#include "sidebarwidget.h"
#include "utils.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  QSplitter *m_mainSplitter;

  SideBarWidget *m_sideBarWidget;

  GraphicsViewWidget *m_graphicsViewWidget;

  LibraryWidget *m_libraryWidget;

  SettingsWidget *m_settingsWidget;

  TextWidget *m_textWidget;

  CenterWidget *m_centerWidget;
};
#endif // MAINWINDOW_H
