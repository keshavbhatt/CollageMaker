#include "colorchooserwidget.h"

#include <QColorDialog>

ColorChooserWidget::ColorChooserWidget(QObject *parent) : QObject{parent} {}

QColor ColorChooserWidget::chooseColor(const QColor &initialColor) {
  return QColorDialog::getColor(initialColor, nullptr, "Choose Color",
                                QColorDialog::ShowAlphaChannel |
                                    QColorDialog::DontUseNativeDialog);
}
