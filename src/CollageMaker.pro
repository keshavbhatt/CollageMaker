QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = collagemaker
TEMPLATE = app

# No debug output in release mode
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# Print if this is a debug or release build
CONFIG(debug, debug|release) {
    message("This is a debug build")
} else {
    message("This is a release build")
}

# Set program version
VERSION = 1.0
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"


APPLICATION_FULLNAME = CollageMaker
DEFINES += APPLICATION_FULLNAME=\\\"$${APPLICATION_FULLNAME}\\\"

# Define git info
GIT_HASH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --short HEAD)\\\""
GIT_BRANCH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --abbrev-ref HEAD)\\\""
BUILD_TIMESTAMP="\\\"$$system(date -u +\""%Y-%m-%dT%H:%M:%SUTC\"")\\\""
DEFINES += GIT_HASH=$$GIT_HASH GIT_BRANCH=$$GIT_BRANCH BUILD_TIMESTAMP=$$BUILD_TIMESTAMP

include(widgets/smartlayout/SmartLayout.pri)
include(widgets/waitingspinner/WaitingSpinner.pri)
include(widgets/elidedlabel/ElidedLabel.pri)
include(widgets/slidingstackwidget/SlidingStackedWidget.pri)

SOURCES += \
    centerwidget.cpp \
    colorchooserwidget.cpp \
    core/medialoader.cpp \
    core/thumbnailgenerator.cpp \
    graphicsscene.cpp \
    graphicsviewwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    pictures/buttonswidget.cpp \
    pictures/libraryimageitemwidget.cpp \
    pictures/libraryitem.cpp \
    pictures/librarywidget.cpp \
    settings/patterns/gridpattern.cpp \
    settings/patterns/mosaicpattern.cpp \
    settings/resolutionmodel.cpp \
    settings/settingscommon.cpp \
    settings/settingswidget.cpp \
    settings/patterns/tilepattern.cpp \
    settings/shared/layoutwidget.cpp \
    sidebarwidget.cpp \
    text/textwidget.cpp \
    utils.cpp

HEADERS += \
    centerwidget.h \
    colorchooserwidget.h \
    core/cookiejar.h \
    core/medialoader.h \
    core/random_useragent.h \
    core/settings_constants.h \
    core/thumbnailgenerator.h \
    graphicsscene.h \
    graphicsviewwidget.h \
    mainwindow.h \
    core/network_manager.h \
    core/settings_manager.h \
    pictures/buttonswidget.h \
    pictures/libraryimageitemwidget.h \
    pictures/libraryitem.h \
    pictures/librarywidget.h \
    settings/patterns/gridpattern.h \
    settings/patterns/mosaicpattern.h \
    settings/patterns/patternbase.h \
    settings/resolutionmodel.h \
    settings/settingscommon.h \
    settings/settingswidget.h \
    settings/patterns/tilepattern.h \
    settings/shared/layoutwidget.h \
    sidebarwidget.h \
    text/textwidget.h \
    utils.h

FORMS += \
    centerwidget.ui \
    mainwindow.ui \
    pictures/buttonswidget.ui \
    pictures/libraryimageitemwidget.ui \
    pictures/librarywidget.ui \
    settings/patterns/gridpattern.ui \
    settings/patterns/mosaicpattern.ui \
    settings/settingswidget.ui \
    settings/patterns/tilepattern.ui \
    settings/shared/layoutwidget.ui \
    sidebarwidget.ui \
    text/textwidget.ui

TRANSLATIONS += \
    CollageMaker_en_IN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
