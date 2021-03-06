/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <chrono>

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlFileSelector>
#include <QtQml/QQmlProperty>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

#include "application/BaseApplication.h"
#include "common/NetworkManager.h"
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "weather/CurrentWeather.h"
#include "weather/models/MapInfoModel.h"
#include "weather/models/MapLayersProxyModel.h"
#include "weather/models/MapLegendProxyModel.h"
#include "weather/models/WeatherMapProxyModel.h"

#ifndef VREMENAR_MOBILE
#include "application/DesktopApplication.h"
#include "application/dialogs/AboutDialog.h"
#include "settings/SettingsDialog.h"
#endif

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QtAndroid>
#endif

#include "ApplicationWindow.h"

namespace Vremenar
{

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QObject(parent),
      _engine(std::make_unique<QQmlApplicationEngine>(this)),
      _network(new NetworkManager(this)),
      _analytics(std::make_unique<Analytics>(_network, this)),
      _localeManager(std::make_unique<LocaleManager>(this)),
      _networkFactory(std::make_unique<NetworkManagerFactory>(this))
{
    // Set the style
#if defined(Q_OS_LINUX) || defined(Q_OS_ANDROID)
    QQuickStyle::setStyle("Material");
#elif defined(Q_OS_WIN)
    QQuickStyle::setStyle("Universal");
#endif

    createModels();
#ifndef VREMENAR_MOBILE
    createWidgets();
#endif

    _engine->addImportPath(QStringLiteral("qrc:/"));

    Qml::registerTypes();

    // Custom file selector
    _qmlFileSelector = new QQmlFileSelector(_engine.get());
#if defined(Q_OS_MACOS)
    _qmlFileSelector->setExtraSelectors({QStringLiteral("nativemenu")});
#elif defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    _qmlFileSelector->setExtraSelectors({QStringLiteral("mobile")});
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
    _qmlFileSelector->setExtraSelectors({QStringLiteral("custommenu")});
#endif

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

    connect(this, &ApplicationWindow::loadInitialMap, this, &ApplicationWindow::startLoadInitialMap);

    // Setup and load main QML
    _engine->setNetworkAccessManagerFactory(_networkFactory.get());
    _engine->load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = gsl::owner<QQuickWindow *>(qobject_cast<QQuickWindow *>(_engine->rootObjects().constFirst()));
    connect(_qmlMainWindow, &QQuickWindow::visibleChanged, this, &ApplicationWindow::visibilityChanged);
#ifdef Q_OS_MACOS
    application->setupTitleBarLessWindow(_qmlMainWindow->winId());
#endif

#ifndef VREMENAR_MOBILE
    // Set application icon
    QIcon appIcon;
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/16x16/vremenar.png"), QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/24x24/vremenar.png"), QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/32x32/vremenar.png"), QSize(32, 32));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/48x48/vremenar.png"), QSize(48, 48));  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/64x64/vremenar.png"), QSize(64, 64));   // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/128x128/vremenar.png"), QSize(128, 128)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    appIcon.addFile(QStringLiteral(":/Vremenar/Logo/logo/256x256/vremenar.png"), QSize(256, 256)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    QGuiApplication::setWindowIcon(appIcon);
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
    _location = std::make_unique<LocationProvider>(this);
    _mapsManager = std::make_unique<MapsManager>(_engine.get(), this);
    _updates = std::make_unique<Updates>(_network, this);
    _weatherProvider = std::make_unique<WeatherProvider>(_network, this);
    connect(_weatherProvider.get(), &WeatherProvider::recordEvent, _analytics.get(), &Analytics::recordEvent);
    connect(_weatherProvider.get(), &WeatherProvider::storeState, this, &ApplicationWindow::writeSettingsStartupMap);

    _engine->rootContext()->setContextProperty(QStringLiteral("Vremenar"), this);
    _engine->rootContext()->setContextProperty(QStringLiteral("VL"), _localeManager.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VUpdates"), _updates.get());

    _engine->rootContext()->setContextProperty(QStringLiteral("VLocation"), _location.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VWeather"), _weatherProvider.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VCurrent"), _weatherProvider->current());
    _engine->rootContext()->setContextProperty(QStringLiteral("VWeatherMapModel"), _weatherProvider->weatherMap());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapInfoModel"), _weatherProvider->mapInfo());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLayersModel"), _weatherProvider->mapLayers());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLegendModel"), _weatherProvider->mapLegend());

    connect(_location.get(), &LocationProvider::positionChanged, _weatherProvider.get(), &WeatherProvider::requestCurrentWeatherInfo);
    connect(_weatherProvider->mapLayers(), &MapLayersProxyModel::typeChanged, _mapsManager.get(), &MapsManager::mapChanged);
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::createWidgets()
{
    Settings settings(this);

    _trayIcon = std::make_unique<TrayIcon>(this);
#ifdef Q_OS_MACOS
    _trayIcon->setVisible(settings.showInTray());
#else
    _trayIcon->setVisible(true);
#endif
    _trayIcon->createMenu({tr("Satellite"), tr("Streets")}, _weatherProvider->mapInfo()->list());
    _trayIcon->setCurrentMap(_weatherProvider->currentMapLayer());

    connect(_trayIcon.get(), &TrayIcon::triggered, this, &ApplicationWindow::toggleVisibility);
    connect(_trayIcon.get(), &TrayIcon::settings, this, &ApplicationWindow::showSettingsDialog);
    connect(_trayIcon.get(), &TrayIcon::quit, QCoreApplication::instance(), &QCoreApplication::quit);
    connect(_trayIcon.get(), &TrayIcon::styleSelected, _weatherProvider.get(), &WeatherProvider::currentMapStyleChanged);
    connect(_trayIcon.get(), &TrayIcon::mapSelected, _weatherProvider.get(), &WeatherProvider::currentMapLayerChanged);
    connect(_weatherProvider.get(), &WeatherProvider::currentMapStyleChangedSignal, _trayIcon.get(), &TrayIcon::setCurrentStyle);
    connect(_weatherProvider.get(), &WeatherProvider::currentMapLayerChangedSignal, _trayIcon.get(), &TrayIcon::setCurrentMap);
    connect(_weatherProvider->current(), &CurrentWeather::stationChanged, _trayIcon.get(), &TrayIcon::setCurrentStation);
    connect(_weatherProvider->current(), &CurrentWeather::conditionChanged, _trayIcon.get(), &TrayIcon::setCurrentCondition);
}

void ApplicationWindow::showAboutDialog()
{
    AboutDialog dialog(_weatherProvider.get());
    dialog.exec();
}

void ApplicationWindow::showSettingsDialog()
{
    gsl::owner<SettingsDialog *> dialog{};
    dialog = new SettingsDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &SettingsDialog::localeChanged, _localeManager.get(), &LocaleManager::setLocale);
    connect(dialog, &SettingsDialog::weatherSourceChanged, this, &ApplicationWindow::weatherSourceChanged);

#ifdef Q_OS_MACOS
    connect(dialog, &SettingsDialog::showInTrayChanged, _trayIcon.get(), &TrayIcon::setVisible);
    connect(dialog, &SettingsDialog::showInDockChanged, this, &ApplicationWindow::dockVisibilityChanged);
#endif

    dialog->show();
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

void ApplicationWindow::startCompleted()
{
    using namespace std::chrono_literals;

    Settings settings(this);
#ifdef Q_OS_MACOS
    Q_EMIT dockVisibilityChanged(settings.showInDock());
#endif

#ifdef Q_OS_ANDROID
    QtAndroid::hideSplashScreen();
#endif

    _ready = true;

    _analytics->beginSession();
    _weatherProvider->requestBaseInfo();

    qDebug() << "Initialization completed";

    _updates->checkVersion();

    QTimer::singleShot(1s, this, &ApplicationWindow::startLoadInitialMap);
}

void ApplicationWindow::startLoadInitialMap()
{
    Settings settings(this);
    if (settings.startupMapEnabled()
        && std::find(_weatherProvider->supportedMapTypes().begin(), _weatherProvider->supportedMapTypes().end(), settings.startupMapType()) != _weatherProvider->supportedMapTypes().end()) {
        _weatherProvider->changeMapType(settings.startupMapType());
    } else {
        _weatherProvider->changeMapType(Weather::MapType::WeatherConditionMap);
    }

    _weatherProvider->startupCompleted();
}

void ApplicationWindow::weatherSourceChanged(int source)
{
    std::vector<Sources::Country> sources = {Sources::Slovenia, Sources::Germany};
    Sources::Country weatherSource = sources[source];

    Settings settings(this);
    if (weatherSource != settings.weatherSource()) {
        settings.setWeatherSource(sources[source]);
        settings.setInitialWeatherSourceChosen(true);
        settings.resetStartupMapCoordinates();
        settings.writeSettings();

        // Do not override startup map coordinates
        _ready = false;
        QCoreApplication::exit(Application::RESTART_CODE);
    } else {
        settings.setInitialWeatherSourceChosen(true);
        settings.writeSettings();
    }
}

} // namespace Vremenar
