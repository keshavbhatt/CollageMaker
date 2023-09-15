#ifndef PATTERNBASE_H
#define PATTERNBASE_H

#include <QObject>
#include <QWidget>

class PatternBase : public QWidget {
  Q_OBJECT
public:
  explicit PatternBase(QWidget *parent = nullptr) : QWidget(parent) {}
  virtual void apply() = 0;
  virtual void showCommonWidgets() = 0;
  virtual ~PatternBase() {}
};

#endif // PATTERNBASE_H
