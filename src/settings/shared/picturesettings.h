#ifndef PICTURESETTINGS_H
#define PICTURESETTINGS_H

#include <QWidget>
#include <graphicsviewwidget.h>

namespace Ui {
class PictureSettings;
}

class PictureSettings : public QWidget {
  Q_OBJECT

public:
  explicit PictureSettings(GraphicsViewWidget *graphicsViewWidget = nullptr,
                           QWidget *parent = nullptr);
  ~PictureSettings();

  void applySettings();
  qreal desiredBorderCornerSize() const;

  QColor desiredBorderColor() const;

  qreal desiredBorderWidth() const;

  private slots:
  void setDesiredOpacity(qreal newDesiredOpacity);
  void setDesiredBorderWidth(qreal newDesiredBorderWidth);
  void chooseBorderColor();

public slots:
  void setDesiredBorderCornerSize(qreal newDesiredBorderCornerSize);

private:
  Ui::PictureSettings *ui;

  GraphicsViewWidget *p_graphicsViewWidget;

  // opacity
  qreal m_desiredOpacity = 1.0;

  // borders
  qreal m_desiredBorderWidth = 0.0;
  QColor m_desiredBorderColor = Qt::white;

  // corner
  qreal m_desiredBorderCornerSize = 0.0;

  void updateBorderColorIndicatorColor(const QColor &color);
  void setDesiredBorderColor(const QColor &newDesiredBorderColor);
};

#endif // PICTURESETTINGS_H
