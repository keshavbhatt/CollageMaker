#ifndef GRAPHICSVIEWWIDGET_H
#define GRAPHICSVIEWWIDGET_H

#include "graphicsscene.h"
#include "imagewidgetitem.h"

#include <QDir>
#include <QFileInfoList>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

#include "settings/settingscommon.h"
#include <utils/gridutils.h>

#include <settings/patterns/patternbase.h>

class GraphicsViewWidget : public QGraphicsView {
  Q_OBJECT
public:
  GraphicsViewWidget(QWidget *parent = nullptr);

  void viewSetCustomSize(const QSize &size);

  GraphicsScene *scene() const;

  qreal scaleFactor() const;

  void zoomView(qreal scaleFactor);

  PatternBase *currentPattern() const;

  void setCurrentPattern(PatternBase *newCurrentPattern);

protected:
  void wheelEvent(QWheelEvent *event) override;

  void resizeEvent(QResizeEvent *event) override;

private:
  GraphicsScene *m_scene;

  bool m_enableFitInView = true;

  PatternBase *m_currentPattern;
};

#endif // GRAPHICSVIEWWIDGET_H
