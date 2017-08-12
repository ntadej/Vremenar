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

#include "ApplicationWindow.h"

ApplicationWindow::ApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent)
{
    createSettings();
    createSettingsStartup();
    createModels();
    createWidgets();

    addImportPath("qrc:/");

    load(QUrl(QStringLiteral("qrc:/main.qml")));

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
}

void ApplicationWindow::createSettingsStartup()
{
}

void ApplicationWindow::createModels()
{
}

void ApplicationWindow::createWidgets()
{
}

void ApplicationWindow::processUrl(const QString &url)
{
    if (url.isEmpty())
        return;

    if (!url.startsWith("vremenar://"))
        return;

    qDebug() << "Opened URL:" << url;
}
