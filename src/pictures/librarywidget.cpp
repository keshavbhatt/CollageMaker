#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <QDebug>
#include <QLabel>
#include <QThread>

LibraryWidget::LibraryWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::LibraryWidget),
      m_mediaLoader(new MediaLoader(this)) {

  ui->setupUi(this);

  //----- init flowLayout
  m_flowLayout = new SmartVerticalFlowLayout(ui->imageViewPortWidget);
  m_flowLayout->setAlignment(Qt::AlignCenter);
  m_flowLayout->setVerticalSpacing(FLOW_LAYOUT_SPACING);
  m_flowLayout->setHorizontalSpacing(FLOW_LAYOUT_SPACING);

  m_flowLayout->setContentsMargins(
      QMargins(FLOW_LAYOUT_MARGIN, FLOW_LAYOUT_MARGIN, FLOW_LAYOUT_MARGIN,
               FLOW_LAYOUT_MARGIN));

  ui->scrollArea->setMinimumWidth((THUMBNAIL_IMAGE_SIZE) +
                                  (FLOW_LAYOUT_MARGIN * 2) +
                                  FLOW_LAYOUT_SPACING + 30);

  ui->imageViewPortWidget->setLayout(m_flowLayout);

  //----- init mediaLoader
  connect(m_mediaLoader, &MediaLoader::filesLoaded, this,
          &LibraryWidget::loadImages);

  updateRemoveMediaButton();

  connect(ui->addImagesPb, &QPushButton::clicked, m_mediaLoader,
          &MediaLoader::loadMediaFiles);

  connect(ui->removeAllImagesPb, &QPushButton::clicked, this,
          &LibraryWidget::removeAllImages);
}

void LibraryWidget::loadImages(const QStringList &imagePaths) {

  if (m_thumbnailGenerator == nullptr) {
    m_thumbnailGenerator = new ThumbnailGenerator();
    m_thumbnailGenerator->setThumbnailSize(
        QSize(THUMBNAIL_IMAGE_SIZE, THUMBNAIL_IMAGE_SIZE));

    connect(m_thumbnailGenerator, &ThumbnailGenerator::thumbnailGenerated, this,
            &LibraryWidget::loadImageToView);
    connect(m_thumbnailGenerator, &ThumbnailGenerator::finished, this,
            &LibraryWidget::thumbnailGenerationFinished);

    // Start the generator in a separate thread
    QThread *thread = new QThread;
    m_thumbnailGenerator->moveToThread(thread);
    thread->start();
    QMetaObject::invokeMethod(m_thumbnailGenerator, "processImages",
                              Qt::QueuedConnection,
                              Q_ARG(QStringList, imagePaths));
  }
}

void LibraryWidget::removeAllImages() {

  // inturrupt thumnail generator
  if (m_thumbnailGenerator != nullptr) {
    m_thumbnailGenerator->thread()->requestInterruption();
  }

  // perform cleanup on m_flowLayout
  while (m_flowLayout->count() > 0) {
    QLayoutItem *item = m_flowLayout->takeAt(m_flowLayout->count() - 1);
    if (item->widget()) {
      item->widget()->setParent(
          nullptr); // this ensure proper cleanup or instant deletion
      item->widget()->deleteLater();
    }
    delete item;
  }

  updateRemoveMediaButton();
}

void LibraryWidget::thumbnailGenerationFinished() {
  QThread *thread = m_thumbnailGenerator->thread();

  if (thread) {
    thread->quit();
    thread->wait();

    delete thread;
  }

  delete m_thumbnailGenerator;
  m_thumbnailGenerator = nullptr;

  updateRemoveMediaButton();
}

void LibraryWidget::loadImageToView(const QPixmap &imageThumbnail) {
  QLabel *imageLabel = new QLabel;
  imageLabel->setPixmap(imageThumbnail);
  m_flowLayout->addWidget(imageLabel);
  updateRemoveMediaButton();
}

void LibraryWidget::updateRemoveMediaButton() {
  ui->removeAllImagesPb->setEnabled(m_flowLayout->count() > 0);
}

LibraryWidget::~LibraryWidget() { delete ui; }
