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

#ifndef VREMENAR_APPLICATIONWINDOW_H_
#define VREMENAR_APPLICATIONWINDOW_H_

#include <memory>

#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>

#include "common/LocaleManager.h"
#include "common/NetworkManagerFactory.h"
#include "location/LocationProvider.h"
#include "weather/arso/ARSOWeatherProvider.h"

#ifndef VREMENAR_MOBILE
#include "application/TrayIcon.h"
#endif

class QQmlFileSelector;
class QQuickWindow;

namespace Vremenar
{
class NetworkManager;

class ApplicationWindow : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QObject *parent = nullptr);

public slots:
    void activate();
    void processUrl(const QString &url);
    void startCompleted();

#ifndef VREMENAR_MOBILE
    void showAboutDialog();
    void showSettingsDialog();
#endif

#ifdef Q_OS_MACOS
    void dockClicked();

signals:
    void dockVisibilityChanged(bool);
#endif

private slots:
    void writeSettingsStartup();

private:
    void createModels();
#ifndef VREMENAR_MOBILE
    void createWidgets();
#endif

    // Application
    NetworkManager *_network; // owned by Qt internally

    std::unique_ptr<LocaleManager> _localeManager;
    std::unique_ptr<LocationProvider> _location;
    std::unique_ptr<NetworkManagerFactory> _networkFactory;

    // API
    std::unique_ptr<ARSO::WeatherProvider> _weatherProvider;

    // QML
    QQmlFileSelector *_qmlFileSelector; // owned by Qt internally
    QQuickWindow *_qmlMainWindow;       // owned by Qt internally

// Widgets
#ifndef VREMENAR_MOBILE
    std::unique_ptr<TrayIcon> _trayIcon;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_APPLICATIONWINDOW_H_
