#include "medialoader.h"

MediaLoader::MediaLoader(QObject *parent) : QObject{parent} {
  // init mime filter list
  auto all_mime_types = m_mimeDb.allMimeTypes();
  for (const QMimeType &mimeType : qAsConst(all_mime_types)) {
    QString type = mimeType.name();
    if (isSupportedImageType(type)) {
      m_mimeFilters << type;
    }
  }
}

bool MediaLoader::isSupportedImageType(QString type) {
  return (
      type.startsWith("image/") &&
      (type.contains("jpg") || type.contains("jpeg") || type.contains("png")));
}

void MediaLoader::loadMediaFiles() {
  QFileDialog fileDialog;
  fileDialog.setMimeTypeFilters(m_mimeFilters);
  // fileDialog.setNameFilter(tr("Images (*.png *.jpg *.jpeg )"));
  fileDialog.setFileMode(QFileDialog::ExistingFiles);
  fileDialog.setWindowTitle(tr("Load Images"));

  if (fileDialog.exec()) {
    QStringList fileNames = fileDialog.selectedFiles();
    emit filesLoaded(fileNames);
  }
}

