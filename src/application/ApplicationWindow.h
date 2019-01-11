/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_APPLICATIONWINDOW_H_
#define VREMENAR_APPLICATIONWINDOW_H_

#include <QtGui/QWindow>
#include <QtQml/QQmlApplicationEngine>

class QQmlFileSelector;
class QQuickWindow;

namespace Vremenar
{
class LocaleManager;
class LocationProvider;
class NetworkManager;
class NetworkManagerFactory;
class SettingsDialog;
class TrayIcon;

namespace ARSO
{
class WeatherProvider;
}

class ApplicationWindow : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QObject *parent = nullptr);
    ~ApplicationWindow();

public slots:
    void activate();
    void processUrl(const QString &url);
    void startCompleted();

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
    std::unique_ptr<SettingsDialog> _settingsDialog;
    std::unique_ptr<TrayIcon> _trayIcon;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_APPLICATIONWINDOW_H_
