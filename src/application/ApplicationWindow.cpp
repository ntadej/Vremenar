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

#include "common/LocaleManager.h"
#include "settings/Settings.h"
#include "settings/SettingsDialog.h"

#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent),
      _localeManager(new LocaleManager(this))
{
    createSettings();
    createSettingsStartup();
    createModels();
    createWidgets();

    addImportPath("qrc:/");

    load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = rootObjects().first();
}

ApplicationWindow::~ApplicationWindow() {}

void ApplicationWindow::activate()
{
    QMetaObject::invokeMethod(_qmlMainWindow, "show");
    QMetaObject::invokeMethod(_qmlMainWindow, "raise");
    QMetaObject::invokeMethod(_qmlMainWindow, "requestActivate");
}

void ApplicationWindow::dockClicked()
{
    QMetaObject::invokeMethod(_qmlMainWindow, "show");
}

void ApplicationWindow::createSettings()
{
    //QScopedPointer<Settings> settings(new Settings(this));

    //qDebug() << "Initialised: Settings";
}

void ApplicationWindow::createSettingsStartup()
{
    QScopedPointer<Settings> settings(new Settings(this));
    _width = settings->width();
    _height = settings->height();
    _posX = settings->posX();
    _posY = settings->posY();

    if (_rememberGui) {
        //resize(_width, _height);
    }

    qDebug() << "Initialised: Startup settings";
}

void ApplicationWindow::createModels()
{
    rootContext()->setContextProperty("Vremenar", this);
    rootContext()->setContextProperty("TNL", _localeManager);
}

void ApplicationWindow::createWidgets()
{
    _settingsDialog = new SettingsDialog();

    connect(_settingsDialog, &SettingsDialog::localeChanged, _localeManager, &LocaleManager::setLocale);

    rootContext()->setContextProperty("VremenarSettings", _settingsDialog);
}

void ApplicationWindow::processUrl(const QString &url)
{
    if (url.isEmpty())
        return;

    if (!url.startsWith("vremenar://"))
        return;

    qDebug() << "Opened URL:" << url;
}
