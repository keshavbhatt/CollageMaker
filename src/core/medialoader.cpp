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

MediaLoader &MediaLoader::getInstance() {
  static MediaLoader instance;
  return instance;
}

bool MediaLoader::isSupportedImageType(QString type) {
  return (
      type.startsWith("image/") &&
      (type.contains("jpg") || type.contains("jpeg") || type.contains("png")));
}

QString MediaLoader::getSelectedImageFileUrl() {
  QFileDialog fileDialog;
  fileDialog.setMimeTypeFilters(m_mimeFilters);
  fileDialog.setFileMode(QFileDialog::ExistingFile);
  fileDialog.setWindowTitle(tr("Select Image"));

  if (fileDialog.exec()) {
    auto selectedFiles = fileDialog.selectedFiles();
    if (!selectedFiles.isEmpty()) {
      return selectedFiles.first();
    }
  }
  return QString();
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
