/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_APPLICATIONWINDOW_H_
#define VREMENAR_APPLICATIONWINDOW_H_

#include <memory>

#include <gsl/pointers>

#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>

#include "application/Updates.h"
#include "application/analytics/Analytics.h"
#include "common/LocaleManager.h"
#include "common/NetworkManagerFactory.h"
#include "maps/LocationProvider.h"
#include "maps/MapsManager.h"
#include "weather/WeatherProvider.h"

#ifndef VREMENAR_MOBILE
#include "application/TrayIcon.h"
#endif

class QQmlFileSelector;
class QQuickWindow;

namespace Vremenar
{
class NetworkManager;

class ApplicationWindow final : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QObject *parent = nullptr);
    ApplicationWindow(const ApplicationWindow &) = delete;
    ApplicationWindow &operator=(ApplicationWindow) = delete;
    ~ApplicationWindow();

public Q_SLOTS:
    void activate();
    void toggleVisibility();
    void visibilityChanged(bool visible);
    void processUrl(const QString &url);
    void startCompleted();
    void startLoadInitialMap();
    void weatherSourceChanged(int source);

#ifndef VREMENAR_MOBILE
    void showAboutDialog();
    void showSettingsDialog();
#endif

#ifdef Q_OS_MACOS
    void dockClicked();

Q_SIGNALS:
    void dockVisibilityChanged(bool);
#endif

Q_SIGNALS:
    void loadInitialMap();

private Q_SLOTS:
#ifndef VREMENAR_MOBILE
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
    std::unique_ptr<QQmlApplicationEngine> _engine{};
    bool _ready{};

    gsl::owner<NetworkManager *> _network{}; // owned by Qt internally

    std::unique_ptr<Analytics> _analytics{};
    std::unique_ptr<LocaleManager> _localeManager{};
    std::unique_ptr<LocationProvider> _location{};
    std::unique_ptr<MapsManager> _mapsManager{};
    std::unique_ptr<NetworkManagerFactory> _networkFactory{};
    std::unique_ptr<Updates> _updates{};

    // API
    std::unique_ptr<WeatherProvider> _weatherProvider{};

    // QML
    gsl::owner<QQmlFileSelector *> _qmlFileSelector{}; // owned by Qt internally
    gsl::owner<QQuickWindow *> _qmlMainWindow{};       // owned by Qt internally

// Widgets
#ifndef VREMENAR_MOBILE
    std::unique_ptr<TrayIcon> _trayIcon{};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_APPLICATIONWINDOW_H_
