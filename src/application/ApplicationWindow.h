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

class QQuickWindow;

class ARSOWeatherProvider;
class SettingsDialog;
class TrayIcon;

namespace Vremenar
{
class LocaleManager;
class LocationProvider;
class NetworkManager;
class NetworkManagerFactory;

class ApplicationWindow : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QObject *parent = nullptr);
    virtual ~ApplicationWindow();

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

    // Settings
    bool _rememberGui;
    int _width;
    int _height;
    int _posX;
    int _posY;

    // Application
    LocaleManager *_localeManager;
    LocationProvider *_location;
    NetworkManager *_network;
    NetworkManagerFactory *_networkFactory;

    // API
    ARSOWeatherProvider *_arso;

    // QML
    QQuickWindow *_qmlMainWindow;

// Widgets
#ifndef VREMENAR_MOBILE
    SettingsDialog *_settingsDialog;
    TrayIcon *_trayIcon;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_APPLICATIONWINDOW_H_
