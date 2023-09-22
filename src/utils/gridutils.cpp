#include "gridutils.h"

GridUtils::GridUtils() {}

QList<QPair<int, int>> GridUtils::findGridCombinations(int numImages) {
  QList<QPair<int, int>> gridCombinations;

  int bestRows = numImages;
  int bestColumns = 1;

  for (int rows = 1; rows <= numImages; ++rows) {
    int columns = (numImages + rows - 1) / rows;

    gridCombinations.append(qMakePair(rows, columns));

    if (rows + columns < bestRows + bestColumns) {
      bestRows = rows;
      bestColumns = columns;
    }
  }

  // Move the best combination to the front of the list
  if (gridCombinations.size() > 1) {
    gridCombinations.move(
        gridCombinations.indexOf(qMakePair(bestRows, bestColumns)), 0);
  }

  return gridCombinations;
}

GridUtils::GridInfo GridUtils::calculateCellSizeForItemCount(
    const QSizeF &sceneSize, int itemCount, qreal spacing, int desiredRows,
    int desiredColumns, qreal borderWidth) {
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

  qreal borderAdjustmentX = borderWidth / 2.0; // Half the border width
  qreal borderAdjustmentY = borderWidth / 2.0; // Half the border width

  QList<QPointF> itemPositions;

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      qreal x = spacing + (itemWidth + spacing) * col;
      qreal y = spacing + (itemHeight + spacing) * row;

      // Adjust the item position to account for the borderWidth
      x += borderAdjustmentX;
      y += borderAdjustmentY;

      // Ensure pixel alignment by rounding to the nearest integer
      qreal roundedX = qRound(x);
      qreal roundedY = qRound(y);
      itemPositions.append(QPointF(roundedX, roundedY));
    }
  }

  // Adjust the item size to exclude the borderWidth
  itemWidth -= borderWidth;
  itemHeight -= borderWidth;

  info.cellSize = QSizeF(itemWidth, itemHeight);
  info.rows = rows;
  info.columns = columns;
  info.itemPositions = itemPositions;

  return info;
}

//GridUtils::GridInfo GridUtils::calculateCellSizeForItemCount(
//    const QSizeF &sceneSize, int itemCount, qreal spacing, int desiredRows,
//    int desiredColumns, qreal borderWidth, qreal shadowOffsetX,
//    qreal shadowOffsetY) {

//  GridInfo info;

//  qreal originalSpacing = spacing; // Store the original spacing

//  int rows = desiredRows;
//  if (desiredRows == 0) {
//    rows = qSqrt(itemCount);
//  }

//  int columns = desiredColumns;
//  if (desiredColumns == 0) {
//    columns = qSqrt(itemCount);
//  }

//  // Calculate the total spacing width and height
//  qreal totalSpacingWidth = (columns)*spacing;
//  qreal totalSpacingHeight = (rows)*spacing;

//  // Adjust item size to include spacing
//  qreal itemWidth = (sceneSize.width() - totalSpacingWidth) / columns;
//  qreal itemHeight = (sceneSize.height() - totalSpacingHeight) / rows;

//  // Adjust item size for spacing when spacing is greater than 0
//  if (originalSpacing > 0) {
//    itemWidth -= originalSpacing / columns; // Use original spacing here
//    itemHeight -= originalSpacing / rows;   // Use original spacing here
//  }

//  qreal op = 0.0;

//  if (shadowOffsetX > shadowOffsetY) {
//    op = shadowOffsetX;
//  } else if (shadowOffsetY > shadowOffsetX) {
//    op = shadowOffsetY;
//  }

//  borderWidth = borderWidth + op;

//  qreal borderAdjustmentX = borderWidth / 2.0; // Half the border width
//  qreal borderAdjustmentY = borderWidth / 2.0; // Half the border width

//  QList<QPointF> itemPositions;

//  for (int row = 0; row < rows; ++row) {
//    for (int col = 0; col < columns; ++col) {
//      qreal x = spacing + (itemWidth + spacing) * col;
//      qreal y = spacing + (itemHeight + spacing) * row;

//      // Adjust the item position to account for the borderWidth
//      x += borderAdjustmentX;
//      y += borderAdjustmentY;

//      // Ensure pixel alignment by rounding to the nearest integer
//      qreal roundedX = qRound(x);
//      qreal roundedY = qRound(y);
//      itemPositions.append(QPointF(roundedX, roundedY));
//    }
//  }

//  // Adjust the item size to exclude the borderWidth
//  itemWidth -= borderWidth + op;
//  itemHeight -= borderWidth + op;

//  info.cellSize = QSizeF(itemWidth, itemHeight);
//  info.rows = rows;
//  info.columns = columns;
//  info.itemPositions = itemPositions;

//  return info;
//}

// GridUtils::GridInfo GridUtils::calculateCellSizeForItemCount(
//     const QSizeF &sceneSize, int itemCount, qreal spacing, int desiredRows,
//     int desiredColumns, qreal borderWidth, qreal shadowOffsetX,
//     qreal shadowOffsetY) {
//   GridInfo info;

//  qreal originalSpacing = spacing; // Store the original spacing

//  int rows = desiredRows;
//  if (desiredRows == 0) {
//    rows = qSqrt(itemCount);
//  }

//  int columns = desiredColumns;
//  if (desiredColumns == 0) {
//    columns = qSqrt(itemCount);
//  }

//  // Calculate the total spacing width and height
//  qreal totalSpacingWidth = (columns)*spacing;
//  qreal totalSpacingHeight = (rows)*spacing;

//  // Adjust item size to include spacing
//  qreal itemWidth = (sceneSize.width() - totalSpacingWidth) / columns;
//  qreal itemHeight = (sceneSize.height() - totalSpacingHeight) / rows;

//  // Adjust item size for spacing when spacing is greater than 0
//  if (originalSpacing > 0) {
//    itemWidth -= originalSpacing / columns; // Use original spacing here
//    itemHeight -= originalSpacing / rows;   // Use original spacing here
//  }

//  qreal borderAdjustmentX = borderWidth / 2.0; // Half the border width
//  qreal borderAdjustmentY = borderWidth / 2.0; // Half the border width

//  qreal op = 0.0;

//  if (shadowOffsetX > shadowOffsetY) {
//    op = shadowOffsetX;
//  } else if (shadowOffsetY > shadowOffsetX) {
//    op = shadowOffsetY;
//  }

//  qreal shadowOffsetAdjustmentX = op / 2.0; // Half the border width
//  qreal shadowOffsetAdjustmentY = op / 2.0; // Half the border width

//  QList<QPointF> itemPositions;

//  for (int row = 0; row < rows; ++row) {
//    for (int col = 0; col < columns; ++col) {
//      qreal x = spacing + (itemWidth + spacing) * col;
//      qreal y = spacing + (itemHeight + spacing) * row;

//      // Adjust the item position to account for the borderWidth
//      x += borderAdjustmentX;
//      y += borderAdjustmentY;

//      // Adjust the item position to account for the shadow offset
//      x += shadowOffsetAdjustmentX;
//      y += shadowOffsetAdjustmentY;

//      // Ensure pixel alignment by rounding to the nearest integer
//      qreal roundedX = qRound(x);
//      qreal roundedY = qRound(y);
//      itemPositions.append(QPointF(roundedX, roundedY));
//    }
//  }

//  // Adjust the item size to exclude the borderWidth and shadow offset
//  itemWidth -= borderWidth + op;//qAbs(shadowOffsetX);
//  itemHeight -= borderWidth + op;//qAbs(shadowOffsetY);

//  info.cellSize = QSizeF(itemWidth, itemHeight);
//  info.rows = rows;
//  info.columns = columns;
//  info.itemPositions = itemPositions;

//  return info;
//}
