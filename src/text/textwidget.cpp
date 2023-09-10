#include "textwidget.h"
#include "ui_textwidget.h"

TextWidget::TextWidget(GraphicsViewWidget *graphicsViewWidget, QWidget *parent)
    : QWidget(parent), ui(new Ui::TextWidget),
      p_graphicsViewWidget(graphicsViewWidget) {
  ui->setupUi(this);

  ui->plainTextEdit->setMaximumHeight(200);
}

TextWidget::~TextWidget() { delete ui; }
