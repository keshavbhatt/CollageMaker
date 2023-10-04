#include "gridutils.h"

GridUtils::GridUtils() {}

QList<QPair<int, int>> GridUtils::findGridRowColumnCombinations(int numImages) {
    QList<QPair<int, int>> gridCombinations;

    int bestRows = numImages;
    int bestColumns = 1;

    // Store the best combinations in case there are multiple
    QList<QPair<int, int>> bestCombinations;

    for (int rows = 1; rows <= numImages; ++rows) {
        int columns = (numImages + rows - 1) / rows;

        gridCombinations.append(qMakePair(rows, columns));

        if (rows + columns < bestRows + bestColumns) {
            // Found a new best combination
            bestRows = rows;
            bestColumns = columns;
            bestCombinations.clear(); // Clear the previous best combinations
            bestCombinations.append(qMakePair(rows, columns));
        } else if (rows + columns == bestRows + bestColumns) {
            // Found another best combination
            bestCombinations.append(qMakePair(rows, columns));
        }
    }

    // Remove combinations that can be swapped
    QList<QPair<int, int>> filteredCombinations;
    for (const auto &combination : gridCombinations) {
        int rows = combination.first;
        int columns = combination.second;

        // Check if the swapped combination is already in the filtered list
        if (!filteredCombinations.contains(qMakePair(columns, rows))) {
            filteredCombinations.append(combination);
        }
    }

    // Move one of the best combinations to the front of the list
    if (!bestCombinations.isEmpty() && filteredCombinations.size() > 1) {
        filteredCombinations.move(
            filteredCombinations.indexOf(bestCombinations.first()), 0);
    }

    return filteredCombinations;
}


GridUtils::GridInfo
GridUtils::calculateCellSizeForItemCount(const QSizeF &sceneSize, int itemCount,
                                         qreal spacing, int desiredRows,
                                         int desiredColumns) {
  GridInfo info;

  qreal originalSpacing = spacing; // Store the original spacing

  int rows = desiredRows;
  if (desiredRows == 0) {
    rows = qSqrt(itemCount);
  }

  int columns = desiredColumns;
  if (desiredColumns == 0) {
    columns = qSqrt(itemCount);
  }

  // Calculate the total spacing width and height
  qreal totalSpacingWidth = (columns)*spacing;
  qreal totalSpacingHeight = (rows)*spacing;

  // Adjust item size to include spacing
  qreal itemWidth = (sceneSize.width() - totalSpacingWidth) / columns;
  qreal itemHeight = (sceneSize.height() - totalSpacingHeight) / rows;

  // Adjust item size for spacing when spacing is greater than 0
  if (originalSpacing > 0) {
    itemWidth -= originalSpacing / columns; // Use original spacing here
    itemHeight -= originalSpacing / rows;   // Use original spacing here
  }

  QList<QPointF> itemPositions;

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      qreal x = spacing + (itemWidth + spacing) * col;
      qreal y = spacing + (itemHeight + spacing) * row;

      // Ensure pixel alignment by rounding to the nearest integer
      qreal roundedX = qRound(x);
      qreal roundedY = qRound(y);

      itemPositions.append(QPointF(roundedX, roundedY));
    }
  }

  info.cellSize = QSizeF(itemWidth, itemHeight);
  info.rows = rows;
  info.columns = columns;
  info.itemPositions = itemPositions;

  return info;
}

