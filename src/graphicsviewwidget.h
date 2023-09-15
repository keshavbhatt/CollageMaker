#ifndef GRAPHICSVIEWWIDGET_H
#define GRAPHICSVIEWWIDGET_H

#include "graphicsscene.h"

#include <QDir>
#include <QFileInfoList>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>

class GraphicsViewWidget : public QGraphicsView {
  Q_OBJECT
public:
  GraphicsViewWidget(QWidget *parent = nullptr);

  void addPixmapItem(const QString &imageFilePath);

  void viewSetCustomSize(const QSize &size);

  GraphicsScene *scene() const;

protected:
  void wheelEvent(QWheelEvent *event) override;

private:
  GraphicsScene *m_scene;
};

#endif // GRAPHICSVIEWWIDGET_H
