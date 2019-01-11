/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlFileSelector>
#include <QtQuick/QQuickWindow>

#include "common/LocaleManager.h"
#include "common/NetworkManager.h"
#include "common/NetworkManagerFactory.h"
#include "location/LocationProvider.h"
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "weather/arso/ARSOWeatherProvider.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"

#ifndef VREMENAR_MOBILE
#include "application/DesktopApplication.h"
#include "application/TrayIcon.h"
#include "settings/SettingsDialog.h"
#endif

#include "ApplicationWindow.h"

namespace Vremenar
{

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent),
      _rememberSize(Settings::DEFAULT_REMEMBER_SIZE),
      _rememberPosition(Settings::DEFAULT_REMEMBER_POSITION),
      _width(Settings::DEFAULT_WIDTH),
      _height(Settings::DEFAULT_HEIGHT),
      _posX(Settings::DEFAULT_POS_X),
      _posY(Settings::DEFAULT_POS_Y),
      _network(new NetworkManager(this)),
      _localeManager(std::make_unique<LocaleManager>(this)),
      _networkFactory(std::make_unique<NetworkManagerFactory>(this))
{
    createModels();
#ifndef VREMENAR_MOBILE
    createWidgets();
#endif

    addImportPath("qrc:/");

    Qml::registerTypes();

    // Custom file selector
    _qmlFileSelector = new QQmlFileSelector(this);
#ifdef Q_OS_MACOS
    _qmlFileSelector->setExtraSelectors({"nativemenu"});
#endif

#ifndef VREMENAR_MOBILE
    auto *application = qobject_cast<DesktopApplication *>(QCoreApplication::instance());

    connect(application, &QCoreApplication::aboutToQuit, this, &ApplicationWindow::writeSettingsStartup);
    connect(application, &DesktopApplication::activate, this, &ApplicationWindow::activate);
    connect(application, &DesktopApplication::urlOpened, this, &ApplicationWindow::processUrl);
#endif

#ifdef Q_OS_MACOS
    connect(application, &DesktopApplication::dockClicked, this, &ApplicationWindow::dockClicked);
    connect(this, &ApplicationWindow::dockVisibilityChanged, application, &DesktopApplication::dockSetVisibility);
#endif

    // Setup and load main QML
    setNetworkAccessManagerFactory(_networkFactory.get());
    load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = qobject_cast<QQuickWindow *>(rootObjects().first());
#ifdef Q_OS_MACOS
    application->setupTitleBarLessWindow(_qmlMainWindow->winId());
#endif
}

ApplicationWindow::~ApplicationWindow() = default;

void ApplicationWindow::activate()
{
    _qmlMainWindow->show();
    _qmlMainWindow->raise();
    _qmlMainWindow->requestActivate();
}

#ifdef Q_OS_MACOS
void ApplicationWindow::dockClicked()
{
    _qmlMainWindow->show();
}
#endif

void ApplicationWindow::writeSettingsStartup()
{
    if (_qmlMainWindow->visibility() == QWindow::Maximized
        || _qmlMainWindow->visibility() == QWindow::FullScreen)
        return;

    Settings settings(this);
    if (settings.rememberPosition()) {
        settings.setPosX(_qmlMainWindow->x());
        settings.setPosY(_qmlMainWindow->y());
    }
    if (settings.rememberSize()) {
        settings.setWidth(_qmlMainWindow->width());
        settings.setHeight(_qmlMainWindow->height());
    }
    settings.writeSettings();
}

void ApplicationWindow::createModels()
{
    _location = std::make_unique<LocationProvider>(this);
    _weatherProvider = std::make_unique<ARSO::WeatherProvider>(_network, this);

    rootContext()->setContextProperty("Vremenar", this);
    rootContext()->setContextProperty("VL", _localeManager.get());

    rootContext()->setContextProperty("VLocation", _location.get());
    rootContext()->setContextProperty("VWeather", _weatherProvider.get());
    rootContext()->setContextProperty("VMapInfoModel", _weatherProvider->mapInfo());
    rootContext()->setContextProperty("VMapLayersModel", _weatherProvider->mapLayers());
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::createWidgets()
{
    Settings settings(this);

    _settingsDialog = std::make_unique<SettingsDialog>();
    _trayIcon = std::make_unique<TrayIcon>(this);
    _trayIcon->setVisible(settings.showInTray());

    connect(_settingsDialog.get(), &SettingsDialog::localeChanged, _localeManager.get(), &LocaleManager::setLocale);
    connect(_settingsDialog.get(), &SettingsDialog::showInTrayChanged, _trayIcon.get(), &TrayIcon::setVisible);
    connect(_trayIcon.get(), &TrayIcon::clicked, this, &ApplicationWindow::activate);

#ifdef Q_OS_MACOS
    connect(_settingsDialog.get(), &SettingsDialog::showInDockChanged, this, &ApplicationWindow::dockVisibilityChanged);
#endif

    rootContext()->setContextProperty("VSettings", _settingsDialog.get());
}
#endif

void ApplicationWindow::processUrl(const QString &url)
{
    if (url.isEmpty())
        return;

    if (!url.startsWith("vremenar://"))
        return;

    qDebug() << "Opened URL:" << url;
}

void ApplicationWindow::startCompleted()
{
#ifdef Q_OS_MACOS
    Settings settings(this);
    emit dockVisibilityChanged(settings.showInDock());
#endif

    _weatherProvider->requestMapLayers(Weather::PrecipitationMap);

    qDebug() << "Initialization completed";
}

} // namespace Vremenar
