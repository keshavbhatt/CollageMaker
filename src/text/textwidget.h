#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <graphicsviewwidget.h>

namespace Ui {
class TextWidget;
}

class TextWidget : public QWidget {
  Q_OBJECT

public:
  explicit TextWidget(GraphicsViewWidget *graphicsViewWidget = nullptr,
                      QWidget *parent = nullptr);
  ~TextWidget();

private:
  Ui::TextWidget *ui;

  GraphicsViewWidget *p_graphicsViewWidget;
};

#endif // TEXTWIDGET_H
