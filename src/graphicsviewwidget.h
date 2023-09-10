#ifndef GRAPHICSVIEWWIDGET_H
#define GRAPHICSVIEWWIDGET_H

#include <QDir>
#include <QFileInfoList>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QObject>

class GraphicsViewWidget : public QGraphicsView {
  Q_OBJECT
public:
  GraphicsViewWidget(QWidget *parent = nullptr);
  void addPixmapItem(const QString &imageFilePath);
  void setCustomSize(const QSize &size);

private:
  QGraphicsScene *m_scene;
};

#endif // GRAPHICSVIEWWIDGET_H
