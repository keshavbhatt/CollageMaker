#ifndef GRIDUTILS_H
#define GRIDUTILS_H

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QtCore>

class GridUtils {

public:
  struct GridInfo {
    QSizeF cellSize;
    int rows;
    int columns;
    QList<QPointF> itemPositions;

    // equality operator for GridInfo
    bool operator==(const GridInfo &other) const {
      return cellSize == other.cellSize && rows == other.rows &&
             columns == other.columns && itemPositions == other.itemPositions;
    }
  };

  struct GridVariant {
    QList<GridInfo> layoutVariants;
  };

  static QList<QPair<int, int>> findGridRowColumnCombinations(int numImages);

  static GridUtils::GridInfo
  calculateCellSizeForItemCount(const QSizeF &sceneSize, int itemCount,
                                qreal spacing, int desiredRows,
                                int desiredColumns);

  static qreal sliderValueToReal(qreal minValue, qreal maxValue,
                                 qreal sliderMaximum, qreal sliderValue);

private:
  GridUtils();
};

#endif // GRIDUTILS_H
