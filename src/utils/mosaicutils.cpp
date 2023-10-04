#include "mosaicutils.h"
#include <QDebug>
#include <QtMath>

MosaicUtils::MosaicLayout MosaicUtils::generateMosaicLayout(int itemCount,
                                                            QSizeF sceneSize) {

  MosaicLayout layout;

  qDebug() << "Generating layout for:";
  qDebug() << "\tItem count:" << itemCount;
  qDebug() << "\tScene Size:" << sceneSize;

  if (itemCount < 1)
    return layout;

  //// row based layout --------

  // row count
  int numRows = qSqrt(itemCount);
  qDebug() << "Rows: " << numRows;

  const int itemsPerRow = itemCount / numRows;
  int randomItemsPerRow = itemsPerRow;

  // range for randomization
  int minRandomValue = itemsPerRow - 1;
  int maxRandomValue = itemsPerRow + 1;

  // generate a random value for randomItemsPerRow within the specified range
  while (randomItemsPerRow == itemsPerRow) {
    randomItemsPerRow =
        QRandomGenerator::global()->bounded(minRandomValue, maxRandomValue);
  }

  qDebug() << "Item per row: " << randomItemsPerRow;

  // item height
  qreal itemHeight = sceneSize.height() / numRows;
  qDebug() << "Item height: " << itemHeight;

  // remaining items
  int remainignItems = 0;
  if (randomItemsPerRow * numRows < itemCount) {
    remainignItems = itemCount - randomItemsPerRow * numRows;
    qDebug() << "We need to adjust" << remainignItems
             << "items within the rows.";
  }

  QList<int> randomRowsForRemainigItems;

  for (int q = 0; q < remainignItems; ++q) {
    int randomRow = QRandomGenerator::global()->bounded(0, numRows);
    randomRowsForRemainigItems << randomRow;
  }

  qDebug() << "Place remaining" << remainignItems << "in"
           << randomRowsForRemainigItems;

  // rows
  for (int r = 0; r < numRows; ++r) {

    // calculate the Y position of the row
    qreal yPos = r * itemHeight;

    // calculate the height for this row
    qreal rowHeight = itemHeight;

    int itemsInThisRow = randomItemsPerRow;
    if (randomRowsForRemainigItems.contains(r)) {

      int count = 0;
      for (int p = 0; p < randomRowsForRemainigItems.size(); ++p) {
        if (randomRowsForRemainigItems.at(p) == r) {
          count++;
        }
      }

      itemsInThisRow = randomItemsPerRow + count;
    }

    qreal itemWidth = sceneSize.width() / itemsInThisRow;

    // calculate the total width of all items in this row
    qreal totalItemWidth = itemsInThisRow * itemWidth;

    // calculate the horizontal spacing between items
    qreal horizontalSpacing =
        (sceneSize.width() - totalItemWidth) / (itemsInThisRow + 1);

    qDebug() << "Row: " << r + 1 << "---------------";

    // place items in each row
    for (int i = 0; i < itemsInThisRow; ++i) {
      // calculate the X position of the item within the row
      qreal xPos = i * (itemWidth + horizontalSpacing) + horizontalSpacing;

      QRectF itemRect(xPos, yPos, itemWidth, rowHeight);

      layout.itemsRects.append(itemRect);

      qDebug() << "\t" << itemRect;
    }
  }

  qDebug() << "------------------------------------------";
  qDebug() << "\n";

  return layout;
}

MosaicUtils::MosaicLayout
MosaicUtils::MosaicUtils::generateMosaicLayout(int itemCount, QSizeF sceneSize,
                                               qreal spacing) {

  MosaicLayout layout;

  qDebug() << "Generating layout for:";
  qDebug() << "\tItem count:" << itemCount;
  qDebug() << "\tScene Size:" << sceneSize;
  qDebug() << "\tSpacing:" << spacing;

  if (itemCount < 1)
    return layout;

  // row count
  int numRows = qSqrt(itemCount);
  qDebug() << "Rows: " << numRows;

  const int itemsPerRow = itemCount / numRows;
  int randomItemsPerRow = itemsPerRow;

  // range for randomization
  int minRandomValue = itemsPerRow - 1;
  int maxRandomValue = itemsPerRow + 1;

  // generate a random value for randomItemsPerRow within the specified range
  while (randomItemsPerRow == itemsPerRow) {
    randomItemsPerRow =
        QRandomGenerator::global()->bounded(minRandomValue, maxRandomValue);
  }

  qDebug() << "Item per row: " << randomItemsPerRow;

  // item height
  qreal itemHeight = (sceneSize.height() - (numRows - 1) * spacing) / numRows;
  qDebug() << "Item height: " << itemHeight;

  // remaining items
  int remainingItems = 0;
  if (randomItemsPerRow * numRows < itemCount) {
    remainingItems = itemCount - randomItemsPerRow * numRows;
    qDebug() << "We need to adjust" << remainingItems
             << "items within the rows.";
  }

  QList<int> randomRowsForRemainingItems;

  for (int q = 0; q < remainingItems; ++q) {
    int randomRow = QRandomGenerator::global()->bounded(0, numRows);
    randomRowsForRemainingItems << randomRow;
  }

  qDebug() << "Place remaining" << remainingItems << "in"
           << randomRowsForRemainingItems;

  // rows
  for (int r = 0; r < numRows; ++r) {

    // calculate the Y position of the row
    qreal yPos = r * (itemHeight + spacing);

    // calculate the height for this row
    qreal rowHeight = itemHeight;

    int itemsInThisRow = randomItemsPerRow;
    if (randomRowsForRemainingItems.contains(r)) {

      int count = 0;
      for (int p = 0; p < randomRowsForRemainingItems.size(); ++p) {
        if (randomRowsForRemainingItems.at(p) == r) {
          count++;
        }
      }

      itemsInThisRow = randomItemsPerRow + count;
    }

    qreal itemWidth =
        (sceneSize.width() - (itemsInThisRow - 1) * spacing) / itemsInThisRow;

    // calculate the horizontal spacing between items
    qreal horizontalSpacing = spacing;

    qDebug() << "Row: " << r + 1 << "---------------";

    // place items in each row
    for (int i = 0; i < itemsInThisRow; ++i) {
      // calculate the X position of the item within the row
      qreal xPos = i * (itemWidth + horizontalSpacing) + horizontalSpacing;

      QRectF itemRect(xPos, yPos, itemWidth, rowHeight);

      layout.itemsRects.append(itemRect);

      qDebug() << "\t" << itemRect;
    }
  }

  qDebug() << "------------------------------------------";
  qDebug() << "\n";

  return layout;
}

MosaicUtils::MosaicUtils() {}
