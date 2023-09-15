#ifndef COLORCHOOSERWIDGET_H
#define COLORCHOOSERWIDGET_H

#include <QColor>
#include <QObject>

class ColorChooserWidget : public QObject {
  Q_OBJECT
public:
  explicit ColorChooserWidget(QObject *parent = nullptr);

signals:

public slots:
  QColor chooseColor(const QColor &initialColor = Qt::white);
};

#endif // COLORCHOOSERWIDGET_H
