#include "buttonswidget.h"
#include "ui_buttonswidget.h"
#include <QPushButton>

ButtonsWidget::ButtonsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ButtonsWidget) {
  ui->setupUi(this);

  setStyleSheet("QWidget#widget{"
                "background-color: rgba(0, 0, 0, 128);"
                "}");

  connect(ui->remove, &QPushButton::clicked, this,
          [=]() { emit removeClicked(); });
}

ButtonsWidget::~ButtonsWidget() { delete ui; }
