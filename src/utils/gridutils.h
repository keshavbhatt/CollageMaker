#ifndef GRIDUTILS_H
#define GRIDUTILS_H

#include <QtCore>

class GridUtils {
public:
  GridUtils();

  struct GridInfo {
    QSizeF cellSize;
    int rows;
    int columns;
    QList<QPointF> itemPositions;

    // Define the equality operator for GridInfo
    bool operator==(const GridInfo &other) const {
      return cellSize == other.cellSize && rows == other.rows &&
             columns == other.columns && itemPositions == other.itemPositions;
    }
  };

  struct GridVariant {
    QList<GridInfo> layoutVariants;
  };

  static QList<QPair<int, int>> findGridCombinations(int numImages);

  static GridUtils::GridInfo
  calculateCellSizeForItemCount(const QSizeF &sceneSize, int itemCount,
                                qreal spacing, int desiredRows,
                                int desiredColumns, qreal borderWidth);
};

#endif // GRIDUTILS_H
