#ifndef LIBRARYIMAGEITEMWIDGET_H
#define LIBRARYIMAGEITEMWIDGET_H

#include "buttonswidget.h"
#include "libraryitem.h"

#include <QEnterEvent>
#include <QWidget>

namespace Ui {
class LibraryImageItemWidget;
}

class LibraryImageItemWidget : public QWidget {
  Q_OBJECT

public:
  explicit LibraryImageItemWidget(
      const QSharedPointer<LibraryItem> &libraryItem,
      QWidget *parent = nullptr);

  ~LibraryImageItemWidget();

signals:
  void removeRequested();

protected:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
#endif

private slots:
  void remove();

private:
  Ui::LibraryImageItemWidget *ui;
  QSharedPointer<LibraryItem> m_libraryItem;

  void showButtons();
  void hideButtons();

  ButtonsWidget *m_buttonsWidget;
  void centerButtonsWidget();
};

#endif // LIBRARYIMAGEITEMWIDGET_H
