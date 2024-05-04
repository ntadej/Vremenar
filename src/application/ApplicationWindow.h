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

#ifndef VREMENAR_APPLICATIONWINDOW_H_
#define VREMENAR_APPLICATIONWINDOW_H_

#include <QtCore/QObject>
#include <QtCore/QString>

#include <gsl/pointers>

#include <memory>

class QQmlApplicationEngine;
class QQmlFileSelector;
class QQuickWindow;

namespace Vremenar
{

class Analytics;
class LocaleManager;
class LocationProvider;
class MapsManager;
class NetworkManager;
class NetworkManagerFactory;
class NotificationsManager;
class Updates;
class WeatherProvider;

#ifndef VREMENAR_MOBILE
class TrayIcon;
#endif

class ApplicationWindow final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ApplicationWindow)
public:
    explicit ApplicationWindow(QObject *parent = nullptr);
    ~ApplicationWindow() final;

public slots:
    void activate();
    void toggleVisibility();
    void visibilityChanged(bool visible);
    void processUrl(const QString &url);
    void startCompleted(QQuickWindow *window,
                        qreal devicePixelRatio = 1.0);
    void weatherSourceChanged(int source);
    void locationSettingChanged(int setting);

#ifndef VREMENAR_MOBILE
public slots:
    void showAboutDialog();
    void showSettingsDialog();
    void showMapsMenu();
    void showSettingsMenu();
    bool shouldQuit();
#endif

#ifdef Q_OS_MACOS
public slots:
    void dockClicked();

signals:
    void dockVisibilityChanged(bool); // NOLINT(readability-named-parameter)
#endif

private slots:
#ifndef VREMENAR_MOBILE
    void updateTrayIcon();
    void writeSettingsStartup();
#endif
    void writeSettingsStartupMap();
    void beforeClose();

private:
    void createModels();
#ifndef VREMENAR_MOBILE
    void createWidgets();
#endif

    // Application
    std::unique_ptr<QQmlApplicationEngine> _engine;
    bool _ready{};

    gsl::owner<NetworkManager *> _network{}; // owned by Qt internally

    std::unique_ptr<Analytics> _analytics;
    std::unique_ptr<LocaleManager> _localeManager;
    std::unique_ptr<LocationProvider> _location;
    std::unique_ptr<MapsManager> _mapsManager;
    std::unique_ptr<NetworkManagerFactory> _networkFactory;
    std::unique_ptr<NotificationsManager> _notificationsManager;
    std::unique_ptr<Updates> _updates;

    // API
    std::unique_ptr<WeatherProvider> _weatherProvider;

    // QML
    gsl::owner<QQmlFileSelector *> _qmlFileSelector{}; // owned by Qt internally
    gsl::owner<QQuickWindow *> _qmlMainWindow{};       // owned by Qt internally

// Widgets
#ifndef VREMENAR_MOBILE
    std::unique_ptr<TrayIcon> _trayIcon;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_APPLICATIONWINDOW_H_
