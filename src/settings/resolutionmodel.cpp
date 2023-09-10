#include "resolutionmodel.h"

ResolutionModel::ResolutionModel(QObject *parent) : QAbstractListModel(parent) {

  // Common resolutions
  resolutions << ResolutionItem{QSize(3840, 2160), "4K UHD"}
              << ResolutionItem{QSize(2560, 1440), "2K QHD"}
              << ResolutionItem{QSize(1920, 1080), "Full HD"}
              << ResolutionItem{QSize(1280, 720), "HD"}
              << ResolutionItem{QSize(800, 600), "SVGA"}
              << ResolutionItem{QSize(640, 480), "VGA"};

  // Common social media resolutions
  resolutions << ResolutionItem{QSize(1200, 628), "Facebook Cover Photo"}
              << ResolutionItem{QSize(1080, 1080), "Instagram Square"}
              << ResolutionItem{QSize(1200, 1200), "Pinterest Square"}
              << ResolutionItem{QSize(1500, 500), "Twitter Header Photo"};

  // Common laptop resolutions
  resolutions << ResolutionItem{QSize(1366, 768), "Laptop WXGA"}
              << ResolutionItem{QSize(1600, 900), "Laptop HD+"}
              << ResolutionItem{QSize(1920, 1200), "Laptop WUXGA"}
              << ResolutionItem{QSize(2560, 1600), "Laptop WQXGA"}
              << ResolutionItem{QSize(2880, 1800), "Laptop Retina"};

  // Common printing sizes (in inches)
  resolutions << ResolutionItem{QSize(8.5 * 300, 11 * 300),
                                "Letter (8.5x11 inches)"}
              << ResolutionItem{QSize(8.27 * 300, 11.69 * 300),
                                "A4 (8.27x11.69 inches)"}
              << ResolutionItem{QSize(4 * 300, 6 * 300),
                                "Postcard (4x6 inches)"}
              << ResolutionItem{QSize(5 * 300, 7 * 300), "5x7 inches"}
              << ResolutionItem{QSize(11 * 300, 14 * 300), "11x14 inches"};
}

ResolutionModel::~ResolutionModel() {}

QVariant ResolutionModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() >= resolutions.size())
    return QVariant();

  if (role == Qt::DisplayRole)
    return resolutions.at(index.row()).displayName;

  return QVariant();
}

int ResolutionModel::rowCount(const QModelIndex &) const {
  return resolutions.size();
}

ResolutionModel::ResolutionItem ResolutionModel::resolution(int index) const {

  if (index >= 0 && index < resolutions.size()) {
    return resolutions.at(index);
  }

  return ResolutionItem{QSize(), ""};
}
