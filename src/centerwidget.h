#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QGraphicsScene>
#include <QWidget>

#include "graphicsviewwidget.h"

namespace Ui {
class CenterWidget;
}

class CenterWidget : public QWidget {
  Q_OBJECT

public:
  explicit CenterWidget(GraphicsViewWidget *graphicsViewWidget = nullptr,
                        QWidget *parent = nullptr);
  ~CenterWidget();

  GraphicsViewWidget *graphicsViewWidget() const;

private slots:
  void on_pushButton_clicked();

private:
  Ui::CenterWidget *ui;
  GraphicsViewWidget *p_graphicsViewWidget;
};

#endif // CENTERWIDGET_H
