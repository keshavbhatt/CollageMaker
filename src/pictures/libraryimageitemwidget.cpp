#include "libraryimageitemwidget.h"
#include "ui_libraryimageitemwidget.h"

#include <memory>

#include <utils.h>

LibraryImageItemWidget::LibraryImageItemWidget(
    const QSharedPointer<LibraryItem> &libraryItem, QWidget *parent)
    : QWidget(parent), ui(new Ui::LibraryImageItemWidget),
      m_libraryItem(libraryItem) {

  ui->setupUi(this);

  if (m_libraryItem->pixmap().isNull() == false) {
    resize(m_libraryItem->pixmap().size());
    ui->label->setPixmap(m_libraryItem->pixmap());
  } else {
    // invalid pixmap
  }

  m_buttonsWidget = new ButtonsWidget(this);
  m_buttonsWidget->setVisible(false);
  m_buttonsWidget->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  connect(m_buttonsWidget, &ButtonsWidget::removeClicked, this,
          &LibraryImageItemWidget::remove);
}

void LibraryImageItemWidget::centerButtonsWidget() {
  if (m_buttonsWidget) {
    m_buttonsWidget->resize(rect().size());
    m_buttonsWidget->move(rect().x(), rect().y());
  }
}

void LibraryImageItemWidget::remove() { emit removeRequested(); }

void LibraryImageItemWidget::showButtons() { m_buttonsWidget->show(); }

void LibraryImageItemWidget::hideButtons() { m_buttonsWidget->hide(); }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void LibraryImageItemWidget::enterEvent(QEnterEvent *event) {
  centerButtonsWidget();
  showButtons();
  move(geometry().x(), geometry().y() - 1);

  QWidget::enterEvent(event);
}

void LibraryImageItemWidget::leaveEvent(QEvent *event) {
  hideButtons();
  move(geometry().x(), geometry().y() + 1);

  QWidget::leaveEvent(event);
}
#else
void LibraryImageItemWidget::enterEvent(QEvent *event) {
  centerButtonsWidget();
  showButtons();
  move(geometry().x(), geometry().y() - 1);

  QWidget::enterEvent(event);
}

void LibraryImageItemWidget::leaveEvent(QEvent *event) {
  hideButtons();
  move(geometry().x(), geometry().y() + 1);

  QWidget::leaveEvent(event);
}
#endif

LibraryImageItemWidget::~LibraryImageItemWidget() { delete ui; }
