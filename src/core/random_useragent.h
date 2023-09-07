#ifndef RANDOM_USERAGENT_H
#define RANDOM_USERAGENT_H

#include <QRandomGenerator>
#include <QString>
#include <QStringList>

class UserAgentGenerator {
public:
  static QString generate() {
    // List of popular web browsers with their latest release version
    QStringList browsers = {
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:91.0) Gecko/20100101 "
        "Firefox/91.0",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Edge/93.0.961.38 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Version/93.0.0.0 Safari/537.36 OPR/79.0.4143.50",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 YaBrowser/21.9.0.1045 Yowser/2.5 "
        "Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 Whale/2.10.123.42 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 Iron/93.0.4800.0 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 Coc Coc Browser/93.0.180 "
        "Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:89.0) Gecko/20100101 "
        "Firefox/89.0",

        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like "
        "Gecko) Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:93.0) Gecko/20100101 "
        "Firefox/93.0",

        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like "
        "Gecko) Brave Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (Macintosh; Intel Mac OS X 11_6_0) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Firefox/93.0",

        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 "
        "(KHTML, like Gecko) Version/15.0 Safari/605.1.15",

        "Mozilla/5.0 (Macintosh; Intel Mac OS X 11_6_0) AppleWebKit/605.1.15 "
        "(KHTML, like Gecko) Version/15.0 Safari/605.1.15",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:93.0) Gecko/20100101 "
        "Firefox/93.0",

        "Mozilla/5.0 (Windows NT 11.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Brave Chrome/93.0.0.0 Safari/537.36",

        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, "
        "like Gecko) Edge/93.0.961.47 Safari/537.36"};

    // Generate a random index from the list of browsers
    int index = QRandomGenerator::global()->bounded(browsers.count());

    // Return the user agent string for the selected browser
    auto version = QRandomGenerator::global()->bounded(93, 112 + 1);
    QString ua = browsers.at(index);
    return ua.replace("93.0", QString::number(version) + ".0");
  }
};
#endif // RANDOM_USERAGENT_H
