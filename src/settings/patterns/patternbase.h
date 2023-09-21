#ifndef PATTERNBASE_H
#define PATTERNBASE_H

#include <QObject>
#include <QWidget>

class PatternBase : public QWidget {
  Q_OBJECT
public:
  explicit PatternBase(QWidget *parent = nullptr) : QWidget(parent) {}

  /**
   * prepare pattern before adding new items to the view.
   *
   * @brief prepare
   */
  virtual void prepare() = 0;

  /**
   * add pixmapItems to view using image file path.
   *
   * @brief addPixmapItemsToView
   * @param imagePaths
   */
  virtual void addPixmapItemsToView(const QStringList &imagePaths) = 0;

  /**
   * apply pattern settings to the view.
   *
   * @brief apply
   */
  virtual void apply() = 0;

  /**
   * request a reload, redraw view using current pattern settings/properties.
   *
   * @brief reload
   */
  virtual void reload() = 0;

  /**
   * show all common widgets that are being shared across all patterns.
   *
   * @brief showCommonWidgets
   */
  virtual void showCommonWidgets() = 0;

  /**
   * destroy pattern.
   *
   * @brief ~PatternBase
   */
  virtual ~PatternBase() {}
};

#endif // PATTERNBASE_H
