/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "ApplicationWindow.h"

#include "application/NotificationsManager.h"
#include "application/Services.h"
#include "application/Updates.h"
#include "application/analytics/Analytics.h"
#include "common/LocaleManager.h"
#include "common/NetworkManager.h"
#include "common/NetworkManagerFactory.h"
#include "location/Location.h"
#include "location/LocationProvider.h"
#include "maps/MapsManager.h"
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "weather/CurrentWeather.h"
#include "weather/Sources.h"
#include "weather/WeatherProvider.h"
#include "weather/models/MapInfoModel.h"
#include "weather/models/MapLayersProxyModel.h"
#include "weather/models/MapLegendProxyModel.h"  // IWYU pragma: keep
#include "weather/models/WeatherAlertModel.h"    // IWYU pragma: keep
#include "weather/models/WeatherMapProxyModel.h" // IWYU pragma: keep

#ifndef VREMENAR_MOBILE
#include "application/DesktopApplication.h"
#include "application/TrayIcon.h"
#include "application/dialogs/AboutDialog.h"
#include "settings/SettingsDialog.h"
#else
#include "application/MobileApplication.h"
#endif

#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
#include "application/ImageProviderMacOSiOS.h"
#endif

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QStringLiteral>
#include <QtGui/QWindow>
#include <QtPositioning/QGeoCoordinate>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlFileSelector>
#include <QtQml/QQmlProperty>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

#include <gsl/pointers>

#include <cstddef>
#include <memory>
#include <vector>

namespace Vremenar
{

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QObject(parent),
      _engine(std::make_unique<QQmlApplicationEngine>(this)),
      _network(new NetworkManager(this)),
      _analytics(std::make_unique<Analytics>(_network, this)),
      _localeManager(std::make_unique<LocaleManager>(this)),
      _networkFactory(std::make_unique<NetworkManagerFactory>(this)),
      _notificationsManager(std::make_unique<NotificationsManager>(_localeManager->locale(), this)),
      _qmlFileSelector(new QQmlFileSelector(_engine.get()))
{
    // Services singleton
    Services::getInstance().setLocaleManager(_localeManager.get());
    Services::getInstance().setNotificationsManager(_notificationsManager.get());

    // Set the style
#if defined(Q_OS_ANDROID)
    QQuickStyle::setStyle(QStringLiteral("Material"));
#elif defined(Q_OS_LINUX) || defined(Q_OS_WINDOWS)
    QQuickStyle::setStyle(QStringLiteral("Universal"));
#else
    QQuickStyle::setStyle(QStringLiteral("Basic"));
#endif

    createModels();
#ifndef VREMENAR_MOBILE
    createWidgets();
#endif

    _engine->addImportPath(QStringLiteral("qrc:/"));
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    _engine->addImageProvider(QStringLiteral("SFSymbols"), new SFSymbolsImageProvider);
#endif

    Qml::registerTypes();

    // Custom file selector
    QStringList extraSelectors;
#if defined(Q_OS_MACOS)
    extraSelectors.append(QStringLiteral("nativemenu"));
    extraSelectors.append(QStringLiteral("nativeicons"));
#elif defined(Q_OS_IOS)
    extraSelectors.append(QStringLiteral("mobile"));
    extraSelectors.append(QStringLiteral("nativeicons"));
#elif defined(Q_OS_ANDROID)
    extraSelectors.append(QStringLiteral("mobile"));
    extraSelectors.append(QStringLiteral("materialstyle"));
#elif defined(Q_OS_LINUX)
    extraSelectors.append(QStringLiteral("custommenu"));
    extraSelectors.append(QStringLiteral("universalstyle"));
#elif defined(Q_OS_WINDOWS)
    extraSelectors.append(QStringLiteral("universalstyle"));
#endif
    if (!extraSelectors.isEmpty()) {
        _qmlFileSelector->setExtraSelectors(extraSelectors);
    }

#ifndef VREMENAR_MOBILE
    auto *application = qobject_cast<DesktopApplication *>(QCoreApplication::instance());
    connect(application, &QCoreApplication::aboutToQuit, this, &ApplicationWindow::writeSettingsStartup);
    connect(application, &DesktopApplication::activate, this, &ApplicationWindow::activate);
    connect(application, &DesktopApplication::urlOpened, this, &ApplicationWindow::processUrl);
#endif
    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, &ApplicationWindow::writeSettingsStartupMap);
    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, &ApplicationWindow::beforeClose);

#ifdef Q_OS_MACOS
    connect(application, &DesktopApplication::dockClicked, this, &ApplicationWindow::dockClicked);
    connect(this, &ApplicationWindow::dockVisibilityChanged, application, &DesktopApplication::dockSetVisibility);
#endif

    // Setup and load main QML
    _engine->setNetworkAccessManagerFactory(_networkFactory.get());
    _engine->load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

#ifndef VREMENAR_MOBILE
    // Set application icon
    QIcon appIcon;
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/16x16/vremenar.png"), QSize(16, 16));     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/24x24/vremenar.png"), QSize(24, 24));     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/32x32/vremenar.png"), QSize(32, 32));     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/48x48/vremenar.png"), QSize(48, 48));     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/64x64/vremenar.png"), QSize(64, 64));     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/128x128/vremenar.png"), QSize(128, 128)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/256x256/vremenar.png"), QSize(256, 256)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    QGuiApplication::setWindowIcon(appIcon);

    const Settings settings;
    QApplication::setQuitOnLastWindowClosed(!settings.showInTray());
#endif
}

ApplicationWindow::~ApplicationWindow()
{
    // Needs to be deleted first
    _engine.reset();
}

void ApplicationWindow::activate()
{
    _qmlMainWindow->show();
    _qmlMainWindow->raise();
    _qmlMainWindow->requestActivate();
}

void ApplicationWindow::toggleVisibility()
{
    if (_qmlMainWindow->isVisible()) {
        _qmlMainWindow->hide();
    } else {
        activate();
    }
}

void ApplicationWindow::visibilityChanged(bool visible)
{
    qDebug() << "Application window visibility changed:" << visible;

    if (visible) {
        _analytics->beginSession();
    } else {
        _analytics->endSession();
    }
}

#ifdef Q_OS_MACOS
void ApplicationWindow::dockClicked()
{
    _qmlMainWindow->show();
}
#endif

void ApplicationWindow::beforeClose()
{
    _analytics->endSession();
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::writeSettingsStartup()
{
    if (_qmlMainWindow->visibility() == QWindow::Maximized
        || _qmlMainWindow->visibility() == QWindow::FullScreen) {
        return;
    }

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
#endif

void ApplicationWindow::writeSettingsStartupMap()
{
    Settings settings(this);
    if (_ready && settings.startupMapEnabled()) {
        auto *mapObject = _qmlMainWindow->findChild<QObject *>(QStringLiteral("mapObject"));

        settings.setStartupMapStyle(_weatherProvider->currentStyle());
        settings.setStartupMapType(_weatherProvider->currentType());

        if (mapObject != nullptr) {
            settings.setStartupMapZoomLevel(QQmlProperty::read(mapObject, QStringLiteral("zoomLevel")).toReal());

            auto center = QQmlProperty::read(mapObject, QStringLiteral("center")).value<QGeoCoordinate>();
            settings.setStartupMapLatitude(center.latitude());
            settings.setStartupMapLongitude(center.longitude());
        }

        settings.writeSettings();
    }
}

void ApplicationWindow::createModels()
{
    _updates = std::make_unique<Updates>(_network, this);
    _weatherProvider = std::make_unique<WeatherProvider>(_network, this);
    connect(_weatherProvider.get(), &WeatherProvider::recordEvent, _analytics.get(), &Analytics::recordEvent);
    connect(_weatherProvider.get(), &WeatherProvider::storeState, this, &ApplicationWindow::writeSettingsStartupMap);

    _engine->rootContext()->setContextProperty(QStringLiteral("Vremenar"), this);
    _engine->rootContext()->setContextProperty(QStringLiteral("VL"), _localeManager.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VNotifications"), _notificationsManager.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VUpdates"), _updates.get());

    _engine->rootContext()->setContextProperty(QStringLiteral("VWeather"), _weatherProvider.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VCurrent"), _weatherProvider->current());
    _engine->rootContext()->setContextProperty(QStringLiteral("VCurrentAlerts"), _weatherProvider->current()->alerts());
    _engine->rootContext()->setContextProperty(QStringLiteral("VWeatherMapModel"), _weatherProvider->weatherMap());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapInfoModel"), _weatherProvider->mapInfo());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLayersModel"), _weatherProvider->mapLayers());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLegendModel"), _weatherProvider->mapLegend());

    _location = std::make_unique<LocationProvider>(_weatherProvider->stations(), this);
    _engine->rootContext()->setContextProperty(QStringLiteral("VLocation"), _location.get());
    connect(_location.get(), &LocationProvider::enabledChanged, _weatherProvider.get(), &WeatherProvider::currentLocationStatusChanged);
    connect(_location.get(), &LocationProvider::positionChanged, _weatherProvider.get(), &WeatherProvider::requestCurrentWeatherInfo);
    connect(_weatherProvider.get(), &WeatherProvider::stationsUpdated, _location.get(), &LocationProvider::locationSettingsChanged);

    _mapsManager = std::make_unique<MapsManager>(_engine.get(), this);
    connect(_weatherProvider->mapLayers(), &MapLayersProxyModel::mapChanged, _mapsManager.get(), &MapsManager::mapChanged);

    connect(_localeManager.get(), &LocaleManager::localeChanged, _notificationsManager.get(), &NotificationsManager::localeChanged);
    connect(_weatherProvider->current(), &CurrentWeather::stationChanged, _notificationsManager.get(), &NotificationsManager::currentStationChanged);

    _location->locationSettingsChanged();
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::createWidgets()
{
    const Settings settings(this);

    _trayIcon = std::make_unique<TrayIcon>(this);
    _trayIcon->setVisible(settings.showInTray());
    updateTrayIcon();

    connect(_trayIcon.get(), &TrayIcon::triggered, this, &ApplicationWindow::toggleVisibility);
    connect(_trayIcon.get(), &TrayIcon::settings, this, &ApplicationWindow::showSettingsDialog);
    connect(_trayIcon.get(), &TrayIcon::checkForUpdates, _updates.get(), &Updates::checkForUpdates);
    connect(_trayIcon.get(), &TrayIcon::about, this, &ApplicationWindow::showAboutDialog);
    connect(_trayIcon.get(), &TrayIcon::quit, QCoreApplication::instance(), &QCoreApplication::quit);
    connect(_trayIcon.get(), &TrayIcon::styleSelected, _weatherProvider.get(), &WeatherProvider::currentMapStyleChanged);
    connect(_trayIcon.get(), &TrayIcon::mapSelected, _weatherProvider.get(), &WeatherProvider::currentMapLayerChanged);
    connect(_localeManager.get(), &LocaleManager::localeChanged, this, &ApplicationWindow::updateTrayIcon);
    connect(_weatherProvider.get(), &WeatherProvider::currentMapStyleChangedSignal, _trayIcon.get(), &TrayIcon::setCurrentStyle);
    connect(_weatherProvider.get(), &WeatherProvider::currentMapLayerChangedSignal, _trayIcon.get(), &TrayIcon::setCurrentMap);
    connect(_weatherProvider->current(), &CurrentWeather::stationChanged, _trayIcon.get(), &TrayIcon::setCurrentStation);
    connect(_weatherProvider->current(), &CurrentWeather::conditionChanged, _trayIcon.get(), &TrayIcon::setCurrentCondition);
    connect(_weatherProvider->mapInfo(), &MapInfoModel::rowsInserted, this, &ApplicationWindow::updateTrayIcon);
}

void ApplicationWindow::updateTrayIcon()
{
    const Settings settings;
    QApplication::setQuitOnLastWindowClosed(!settings.showInTray());

    _trayIcon->setVisible(settings.showInTray());

    _trayIcon->createMenu({tr("Satellite"), tr("Streets (Light)"), tr("Streets (Dark)")}, _weatherProvider->mapInfo()->list());
    _trayIcon->setCurrentStyle(_weatherProvider->currentMapStyle());
    _trayIcon->setCurrentMap(_weatherProvider->currentMapLayer());
}

void ApplicationWindow::showAboutDialog()
{
    AboutDialog dialog(_weatherProvider.get());
    dialog.exec();
}

void ApplicationWindow::showSettingsDialog()
{
    gsl::owner<SettingsDialog *> dialog{};
    dialog = new SettingsDialog(_weatherProvider->stationsWithCurrentCondition(), _notificationsManager->nativeSupported());
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &SettingsDialog::localeChanged, _localeManager.get(), &LocaleManager::setLocale);
    connect(dialog, &SettingsDialog::locationChanged, _location.get(), &LocationProvider::locationSettingsChanged);
    connect(dialog, &SettingsDialog::weatherSourceChanged, this, &ApplicationWindow::weatherSourceChanged);

    connect(dialog, &SettingsDialog::showInTrayChanged, this, &ApplicationWindow::updateTrayIcon);
#ifdef Q_OS_MACOS
    connect(dialog, &SettingsDialog::showInDockChanged, this, &ApplicationWindow::dockVisibilityChanged);
#endif

    if (_notificationsManager->nativeSupported()) {
        connect(dialog, &SettingsDialog::notificationsChanged, _notificationsManager.get(), &NotificationsManager::settingsChanged);
        connect(_notificationsManager.get(), &NotificationsManager::nativeEnabledStatus, dialog, &SettingsDialog::notificationsStatus);
        _notificationsManager->nativeEnabledCheck();
    }

    dialog->show();
}

void ApplicationWindow::showMapsMenu()
{
    _trayIcon->showMapsMenu(QCursor::pos());
}

void ApplicationWindow::showSettingsMenu()
{
    _trayIcon->showSettingsMenu(QCursor::pos());
}

bool ApplicationWindow::shouldQuit()
{
    return !_trayIcon->isVisible();
}
#endif

void ApplicationWindow::processUrl(const QString &url)
{
    if (url.isEmpty()) {
        return;
    }

    if (!url.startsWith(QStringLiteral("vremenar://"))) {
        return;
    }

    qDebug() << "Opened URL:" << url;
}

void ApplicationWindow::startCompleted(QQuickWindow *window,
                                       qreal devicePixelRatio)
{
    const Settings settings(this);
#ifdef Q_OS_MACOS
    emit dockVisibilityChanged(settings.showInDock());
#endif

#ifdef Q_OS_ANDROID
    QNativeInterface::QAndroidApplication::hideSplashScreen();
#endif

    // NOLINTNEXTLINE(google-readability-casting)
    _qmlMainWindow = gsl::owner<QQuickWindow *>(window);
    connect(_qmlMainWindow, &QQuickWindow::visibleChanged, this, &ApplicationWindow::visibilityChanged);
#if defined(Q_OS_MACOS)
    auto *application = qobject_cast<DesktopApplication *>(QCoreApplication::instance());
    application->setupTitleBarLessWindow(window->winId(), devicePixelRatio);
#else
    Q_UNUSED(devicePixelRatio)
#endif

    _ready = true;

    _analytics->beginSession();
    _weatherProvider->requestStations();

    qDebug() << "Initialization completed";

    _updates->checkVersion();
}

void ApplicationWindow::weatherSourceChanged(int source)
{
    auto index = static_cast<std::size_t>(source);
    std::vector<Sources::Country> sources = {Sources::Slovenia, Sources::Germany};
    const Sources::Country weatherSource = sources[index];

    Settings settings(this);
    if (weatherSource != settings.weatherSource()) {
        settings.setWeatherSource(sources[index]);
        settings.setWeatherSourceInitialChoice(true);
        settings.resetStartupMapCoordinates();
        settings.writeSettings();

        _weatherProvider->resetSource();
        _location->resetPosition();

        auto *mapObject = _qmlMainWindow->findChild<QObject *>(QStringLiteral("mapObject"));
        if (mapObject != nullptr) {
            QMetaObject::invokeMethod(mapObject, "reinitPosition");
        }
    } else {
        settings.setWeatherSourceInitialChoice(true);
        settings.writeSettings();
    }
}

void ApplicationWindow::locationSettingChanged(int setting)
{
    Settings settings(this);
    if (setting == 1) {
        settings.setLocationSource(Location::Disabled);
    } else {
        settings.setLocationSource(Location::Automatic);
    }
    settings.setLocationInitialChoice(true);
    settings.writeSettings();

    _location->locationSettingsChanged();
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_ApplicationWindow.cpp"
// NOLINTEND
