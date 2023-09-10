#ifndef RESOLUTIONMODEL_H
#define RESOLUTIONMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QSize>
#include <QVariant>

class ResolutionModel : public QAbstractListModel {
  Q_OBJECT

public:
  struct ResolutionItem {
    QSize size;
    QString name;
    QString displayName; // combined name and size

    // Constructor
    ResolutionItem(const QSize &s, const QString &n)
        : size(s), name(n), displayName(QString("%1 (%2x%3)")
                                            .arg(name)
                                            .arg(size.width())
                                            .arg(size.height())) {}
  };

  ~ResolutionModel();

  ResolutionModel(QObject *parent = nullptr);

  // QAbstractListModel implementation
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  // Custom function to retrieve a resolution
  ResolutionItem resolution(int index) const;

private:
  QList<ResolutionItem> resolutions;
};

#endif // RESOLUTIONMODEL_H
