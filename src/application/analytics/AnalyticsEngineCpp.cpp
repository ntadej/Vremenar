/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QDebug>
#include <QtCore/QSysInfo>
#include <QtCore/QUuid>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include "application/analytics/AnalyticsEngineCpp.h"
#include "settings/Settings.h"

#include "Config.h"

namespace Vremenar
{

AnalyticsEngineCpp::AnalyticsEngineCpp(NetworkManager *network)
{
    QString deviceId = QSysInfo::machineUniqueId();
    if (deviceId.isEmpty()) {
        Settings settings;
        deviceId = settings.uuid();
        if (deviceId.isEmpty()) {
            deviceId = QUuid::createUuid().toString();
            settings.setUuid(deviceId);
        }
    }

#ifdef Q_OS_WINDOWS
    QString platform = QStringLiteral("Windows");
#else
    QString platform = QStringLiteral("Linux");
#endif

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    QString screenSize = QString::number(width) + "x" + QString::number(height);

    QString productName = QSysInfo::prettyProductName();
    QString kernelVersion = QSysInfo::kernelVersion().split(QStringLiteral("-")).first();

    qDebug() << "Initializing Countly" << productName << kernelVersion << screenSize;

    _countly = std::make_unique<Countly>(network);
    // OS, OS_version, device, resolution, carrier, app_version);
    _countly->setMetrics(platform, kernelVersion, productName, screenSize, Vremenar::version.data());
    _countly->setDeviceID(deviceId);
    _countly->setSalt(Vremenar::CountlySalt.data());
    _countly->start(Vremenar::CountlyAppKey.data(), Vremenar::CountlyEndpoint.data());
}

void AnalyticsEngineCpp::beginSession() const
{
    _countly->beginSession();
}

void AnalyticsEngineCpp::updateSession() const
{
    _countly->updateSession();
}

void AnalyticsEngineCpp::endSession() const
{
    _countly->endSession();
}

void AnalyticsEngineCpp::recordEvent(const QString &event) const
{
    Q_UNUSED(event)

    // Events not supported at the moment
    // _countly->recordEvent(event, 1);
}

} // namespace Vremenar
