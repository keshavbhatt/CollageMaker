#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "core/medialoader.h"
#include "core/thumbnailgenerator.h"
#include "graphicsviewwidget.h"
#include "libraryitem.h"
#include "smartverticalflowlayout.h"

namespace Ui {
class LibraryWidget;
}

struct LibraryItemData {
  QSharedPointer<LibraryItem> libraryItem;
  QString filePath;
};

class LibraryWidget : public QWidget {
  Q_OBJECT

public:
  explicit LibraryWidget(GraphicsViewWidget *graphicsViewWidget = nullptr,
                         QWidget *parent = nullptr);
  ~LibraryWidget();

  QStringList getLoadedImagePath();

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

  GraphicsViewWidget *p_graphicsViewWidget;

  std::vector<LibraryItemData> m_libraryItemData;

  void updateRemoveMediaButton();

  void loadImages(const QStringList &imagePaths);
  void loadImageToView(const QPixmap &imageThumbnail, const QString &imagePath);
  void thumbnailGenerationFinished();
  void updateImageCount();
};

#endif // LIBRARYWIDGET_H
