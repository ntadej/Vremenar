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
#include "qml/Qml.h"
#include "settings/Settings.h"
#include "settings/SettingsDialog.h"

#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent),
      _localeManager(new LocaleManager(this))
{
    createModels();
    createWidgets();

    addImportPath("qrc:/");

    Vremenar::Qml::registerTypes();

    load(QUrl(QStringLiteral("qrc:/Vremenar/main.qml")));

    _qmlMainWindow = qobject_cast<QQuickWindow *>(rootObjects().first());

    connect(qApp, &QCoreApplication::aboutToQuit, this, &ApplicationWindow::writeSettingsStartup);
}

ApplicationWindow::~ApplicationWindow() {}

void ApplicationWindow::activate()
{
    _qmlMainWindow->show();
    _qmlMainWindow->raise();
    _qmlMainWindow->requestActivate();
}

void ApplicationWindow::dockClicked()
{
    _qmlMainWindow->show();
}

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
