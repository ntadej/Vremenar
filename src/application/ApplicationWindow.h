/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_APPLICATIONWINDOW_H_
#define VREMENAR_APPLICATIONWINDOW_H_

#include <QtGui/QCloseEvent>
#include <QtQml/QQmlApplicationEngine>

class QQuickWindow;

class LocaleManager;
class SettingsDialog;
class TrayIcon;

class ApplicationWindow : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit ApplicationWindow(QObject *parent = 0);
    virtual ~ApplicationWindow();

public slots:
    void activate();
    void dockClicked();
    void processUrl(const QString &url);

private slots:
    void writeSettingsStartup();

private:
    void createModels();
    void createWidgets();

    // Settings
    bool _rememberGui;
    int _width;
    int _height;
    int _posX;
    int _posY;

    // Application
    LocaleManager *_localeManager;

    // QML
    QQuickWindow *_qmlMainWindow;

    // Widgets
    SettingsDialog *_settingsDialog;
    TrayIcon *_trayIcon;
};

#endif // VREMENAR_APPLICATIONWINDOW_H_
