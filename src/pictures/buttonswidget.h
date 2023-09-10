#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H

#include <QWidget>

namespace Ui {
class ButtonsWidget;
}

class ButtonsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonsWidget(QWidget *parent = nullptr);
    ~ButtonsWidget();

signals:
    void removeClicked();

private:
    Ui::ButtonsWidget *ui;
};

#endif // BUTTONSWIDGET_H
