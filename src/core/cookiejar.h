#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QDataStream>
#include <QDateTime>
#include <QFile>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QTimer>
#include <QTimerEvent>

const quint8 cookieFileVersion = 1;

class CookieJar : public QNetworkCookieJar {
  Q_OBJECT

public:
  CookieJar(const QString &cookieFileName, QObject *parent = nullptr)
      : QNetworkCookieJar(parent), m_cookieFileName(cookieFileName) {
    load();
  }

  ~CookieJar() {
    if (m_cookieSavingTimer.isActive())
      save();
  }

  void save() {
    expireCookies();

    QByteArray cookieData;
    QDataStream stream(&cookieData, QIODevice::WriteOnly);
    stream << cookieFileVersion;
    QList<QNetworkCookie> cookies = allCookies();

    QMutableListIterator<QNetworkCookie> it(cookies);
    while (it.hasNext()) {
      if (it.next().isSessionCookie())
        it.remove();
    }

    stream << qint32(cookies.count());
    foreach (const QNetworkCookie &cookie, cookies)
      stream << cookie.toRawForm();

    QFile cookieFile(m_cookieFileName + ".tmp");
    if (!cookieFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
      return;

    cookieFile.write(cookieData);
    cookieFile.close();
    // ### use atomic rename
    QFile::remove(m_cookieFileName);
    cookieFile.rename(m_cookieFileName);
  }

  void load() {
    QFile cookieFile(m_cookieFileName);
    if (!cookieFile.open(QIODevice::ReadOnly))
      return;

    QDataStream stream(&cookieFile);
    quint8 version;
    stream >> version;
    if (version != cookieFileVersion)
      return;

    QList<QNetworkCookie> cookies;
    qint32 count;
    stream >> count;

#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
    cookies.reserve(count);
#endif
    for (int i = 0; i < count && !stream.atEnd(); ++i) {
      QByteArray rawCookie;
      stream >> rawCookie;
      cookies += QNetworkCookie::parseCookies(rawCookie);
    }

    setAllCookies(cookies);

    expireCookies();
  }

  bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList,
                         const QUrl &url) {
    bool cookiesAdded = QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
    if (!m_cookieSavingTimer.isActive())
      // Save cookies maximum 30 seconds after any modification
      m_cookieSavingTimer.start(1000 * 30);
    return cookiesAdded;
  }

  void timerEvent(QTimerEvent *ev) {
    if (ev->timerId() == m_cookieSavingTimer.timerId()) {
      save();
      m_cookieSavingTimer.stop();
      return;
    }
    return QObject::timerEvent(ev);
  }

  void expireCookies() {
    const QList<QNetworkCookie> &currentCookies = allCookies();
    QList<QNetworkCookie> newCookies;
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
    newCookies.reserve(currentCookies.count());
#endif
    QDateTime now = QDateTime::currentDateTime();
    foreach (const QNetworkCookie &cookie, currentCookies) {
      if (!cookie.isSessionCookie() && cookie.expirationDate() < now)
        continue;
      newCookies += cookie;
    }
    setAllCookies(newCookies);
  }

  void clearCookieJar() {
    if (m_cookieSavingTimer.isActive())
      m_cookieSavingTimer.stop();

    setAllCookies(QList<QNetworkCookie>());
    save();
  }

private:
  QString m_cookieFileName;
  QTimer m_cookieSavingTimer;
};

#endif // COOKIEJAR_H
