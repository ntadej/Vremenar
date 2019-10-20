/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlFileSelector>
#include <QtQuick/QQuickWindow>

#include "common/NetworkManager.h"
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "weather/common/models/MapInfoModel.h"
#include "weather/common/models/MapLayersProxyModel.h"
#include "weather/common/models/MapLegendProxyModel.h"

#ifndef VREMENAR_MOBILE
#include "application/DesktopApplication.h"
#include "application/dialogs/AboutDialog.h"
#include "settings/SettingsDialog.h"
#endif

#include "ApplicationWindow.h"

namespace Vremenar
{

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QObject(parent),
      _engine(std::make_unique<QQmlApplicationEngine>(this)),
      _network(new NetworkManager(this)),
      _localeManager(std::make_unique<LocaleManager>(this)),
      _networkFactory(std::make_unique<NetworkManagerFactory>(this))
{
    createModels();
#ifndef VREMENAR_MOBILE
    createWidgets();
#endif

    _engine->addImportPath(QStringLiteral("qrc:/"));

    Qml::registerTypes();

    // Custom file selector
    _qmlFileSelector = new QQmlFileSelector(_engine.get());
#ifdef Q_OS_MACOS
    _qmlFileSelector->setExtraSelectors({QStringLiteral("nativemenu")});
#endif
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    _qmlFileSelector->setExtraSelectors({QStringLiteral("mobile")});
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
    _engine->setNetworkAccessManagerFactory(_networkFactory.get());
    _engine->load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = qobject_cast<QQuickWindow *>(_engine->rootObjects().constFirst());
#ifdef Q_OS_MACOS
    application->setupTitleBarLessWindow(_qmlMainWindow->winId());
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

#ifdef Q_OS_MACOS
void ApplicationWindow::dockClicked()
{
    _qmlMainWindow->show();
}
#endif

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

void ApplicationWindow::createModels()
{
    _location = std::make_unique<LocationProvider>(this);
    _weatherProvider = std::make_unique<ARSO::WeatherProvider>(_network, this);

    _engine->rootContext()->setContextProperty(QStringLiteral("Vremenar"), this);
    _engine->rootContext()->setContextProperty(QStringLiteral("VL"), _localeManager.get());

    _engine->rootContext()->setContextProperty(QStringLiteral("VLocation"), _location.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VWeather"), _weatherProvider.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapInfoModel"), _weatherProvider->mapInfo());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLayersModel"), _weatherProvider->mapLayers());
    _engine->rootContext()->setContextProperty(QStringLiteral("VMapLegendModel"), _weatherProvider->mapLegend());
}

#ifndef VREMENAR_MOBILE
void ApplicationWindow::createWidgets()
{
    Settings settings(this);

    _trayIcon = std::make_unique<TrayIcon>(this);
    _trayIcon->setVisible(settings.showInTray());

    connect(_trayIcon.get(), &TrayIcon::clicked, this, &ApplicationWindow::activate);
}

void ApplicationWindow::showAboutDialog()
{
    AboutDialog dialog(_weatherProvider.get());
    dialog.exec();
}

void ApplicationWindow::showSettingsDialog()
{
    auto dialog = new SettingsDialog();
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &SettingsDialog::localeChanged, _localeManager.get(), &LocaleManager::setLocale);
    connect(dialog, &SettingsDialog::showInTrayChanged, _trayIcon.get(), &TrayIcon::setVisible);

#ifdef Q_OS_MACOS
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
#ifdef Q_OS_MACOS
    Settings settings(this);
    Q_EMIT dockVisibilityChanged(settings.showInDock());
#endif

    _weatherProvider->changeMapType(Weather::PrecipitationMap);

    qDebug() << "Initialization completed";
}

} // namespace Vremenar
