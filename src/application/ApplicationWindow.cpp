/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include "common/LocaleManager.h"
#include "common/NetworkManager.h"
#include "common/NetworkManagerFactory.h"
#include "location/LocationProvider.h"
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "weather/arso/ARSOWeatherProvider.h"

#ifndef VREMENAR_MOBILE
#include "application/DesktopApplication.h"
#include "application/TrayIcon.h"
#include "settings/SettingsDialog.h"
#endif

#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent),
      _localeManager(new LocaleManager(this)),
      _network(new NetworkManager(this)),
      _networkFactory(new NetworkManagerFactory(this))
{
    createModels();
#ifndef VREMENAR_MOBILE
    createWidgets();
#endif

    addImportPath("qrc:/");

    Vremenar::Qml::registerTypes();

#ifndef VREMENAR_MOBILE
    connect(qApp, &QCoreApplication::aboutToQuit, this, &ApplicationWindow::writeSettingsStartup);

    DesktopApplication *application = qobject_cast<DesktopApplication *>(qApp);
    connect(application, &DesktopApplication::activate, this, &ApplicationWindow::activate);
    connect(application, &DesktopApplication::urlOpened, this, &ApplicationWindow::processUrl);
#endif

#ifdef Q_OS_MACOS
    connect(application, &DesktopApplication::dockClicked, this, &ApplicationWindow::dockClicked);
    connect(this, &ApplicationWindow::dockVisibilityChanged, application, &DesktopApplication::dockSetVisibility);
#endif

    // Setup and load main QML
    setNetworkAccessManagerFactory(_networkFactory);
    load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = qobject_cast<QQuickWindow *>(rootObjects().first());
#ifdef Q_OS_MACOS
    application->setupTitleBarLessWindow(_qmlMainWindow->winId());
#endif
}

ApplicationWindow::~ApplicationWindow() {}

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

    QScopedPointer<Settings> settings(new Settings(this));
    if (settings->rememberPosition()) {
        settings->setPosX(_qmlMainWindow->x());
        settings->setPosY(_qmlMainWindow->y());
    }
    if (settings->rememberSize()) {
        settings->setWidth(_qmlMainWindow->width());
        settings->setHeight(_qmlMainWindow->height());
    }
    settings->writeSettings();
}

void ApplicationWindow::createModels()
{
    _location = new LocationProvider(this);
    _arso = new ARSOWeatherProvider(_network, this);

    rootContext()->setContextProperty("Vremenar", this);
    rootContext()->setContextProperty("VL", _localeManager);

    rootContext()->setContextProperty("VLocation", _location);
    rootContext()->setContextProperty("VWeather", _arso);
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::createWidgets()
{
    QScopedPointer<Settings> settings(new Settings(this));

    _settingsDialog = new SettingsDialog();
    _trayIcon = new TrayIcon(this);
    _trayIcon->setVisible(settings->showInTray());

    connect(_settingsDialog, &SettingsDialog::localeChanged, _localeManager, &LocaleManager::setLocale);
    connect(_settingsDialog, &SettingsDialog::showInTrayChanged, _trayIcon, &TrayIcon::setVisible);
    connect(_trayIcon, &TrayIcon::clicked, this, &ApplicationWindow::activate);

#ifdef Q_OS_MACOS
    connect(_settingsDialog, &SettingsDialog::showInDockChanged, this, &ApplicationWindow::dockVisibilityChanged);
#endif

    rootContext()->setContextProperty("VremenarSettings", _settingsDialog);
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
    QScopedPointer<Settings> settings(new Settings(this));
    emit dockVisibilityChanged(settings->showInDock());
#endif

    _arso->requestMapLayers(Vremenar::Weather::PrecipitationMap);

    qDebug() << "Initialization completed";
}
