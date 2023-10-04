#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QStandardPaths>

#include "cookiejar.h"
#include "random_useragent.h"
#include "settings_manager.h"
#include <utils/commonutils.h>

/**
 * @brief The NetworkManager singleton class
 */
class NetworkManager : public QObject {
  Q_OBJECT
public:
  static NetworkManager &instanceRef() {
    static NetworkManager manager;
    return manager;
  }

  static NetworkManager *instancePtr() { return &instanceRef(); }

  virtual ~NetworkManager() { m_manager.deleteLater(); }

  QNetworkReply *get(const QUrl &url) {
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::UserAgentHeader, m_userAgentString);

    // Set the cache policy to prefer cached data
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                         QNetworkRequest::PreferCache);

    // allow redirect
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::downloadProgress, this,
            &NetworkManager::onDownloadProgress, Qt::UniqueConnection);

    return reply;
  }

  QNetworkReply *post(const QUrl &url, const QByteArray &data) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, m_userAgentString);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");

    QNetworkReply *reply = m_manager.post(request, data);

    return reply;
  }

  qint64 totalBytesDownloaded() const { return m_totalBytesDownloaded; }

signals:
  void totalBytesDownloadedChanged(const qint64 &bytesRecieved);

private:
  NetworkManager() {

    // read value from settings to restore counter from today's usage
    //    m_totalBytesDownloaded = SettingsManager::instance()
    //                                 .settings()
    //                                 .value(SETTINGS_TODAY_DATA_USAGE, 0)
    //                                 .toInt();

    connect(&m_manager, &QNetworkAccessManager::sslErrors, this,
            &NetworkManager::onSslErrors);

    // Create a disk cache object and set it as the cache for the network
    // manager
    m_diskCache = new QNetworkDiskCache(this);
    m_diskCache->setCacheDirectory(
        QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    m_diskCache->setMaximumCacheSize(250 * 1024 * 1024); // 250 MB
    m_manager.setCache(m_diskCache);

    // Cookiejar
    QString cookieJarPath = CommonUtils::getWritableDataPath(
                                QStandardPaths::AppDataLocation, "cookie") +
                            QDir::separator() + "jar.dat";
    auto cookieJar = new CookieJar(cookieJarPath);
    m_manager.setCookieJar(cookieJar);

    qDebug() << "NetworkManager"
             << "using UA" << m_userAgentString;
  }

  void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    reply->ignoreSslErrors(errors);
  }

  void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal) {

    if (bytesReceived == bytesTotal) {
      m_totalBytesDownloaded += bytesReceived;
      emit totalBytesDownloadedChanged(m_totalBytesDownloaded);
    }
  }

  QNetworkAccessManager m_manager;

  QNetworkDiskCache *m_diskCache;

  QString m_userAgentString = UserAgentGenerator::generate();

  qint64 m_totalBytesDownloaded = 0;
};

#endif // NETWORK_MANAGER_H
