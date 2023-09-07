#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "core/medialoader.h"
#include "core/thumbnailgenerator.h"
#include "smartverticalflowlayout.h"

namespace Ui {
class LibraryWidget;
}

class LibraryWidget : public QWidget {
  Q_OBJECT

public:
  explicit LibraryWidget(QWidget *parent = nullptr);
  ~LibraryWidget();

  private slots:
  void removeAllImages();
  private:
  Ui::LibraryWidget *ui;

  SmartVerticalFlowLayout *m_flowLayout;

  // used to trigger optimize viewport calls
  int LAST_VSCROLL_VALUE = 0;

  // used to set viewport's layout margins
  int FLOW_LAYOUT_MARGIN = 12;

  // used to set viewport's layout spacing
  int FLOW_LAYOUT_SPACING = 16;

  // size of image thumbnail in library widget
  int THUMBNAIL_IMAGE_SIZE = 180;

  ThumbnailGenerator *m_thumbnailGenerator = nullptr;

  MediaLoader *m_mediaLoader;

  void updateRemoveMediaButton();

  void loadImages(const QStringList &imagePaths);
  void loadImageToView(const QPixmap &imageThumbnail);
  void thumbnailGenerationFinished();
};

#endif // LIBRARYWIDGET_H
