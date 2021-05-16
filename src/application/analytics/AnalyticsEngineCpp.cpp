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
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <Countly/Countly.h>

#include "application/analytics/AnalyticsEngineCpp.h"

#include "Config.h"

namespace Vremenar
{

AnalyticsEngineCpp::AnalyticsEngineCpp()
{
    std::string deviceId = QSysInfo::machineUniqueId().toStdString();
#ifdef Q_OS_WIN
    std::string platform = "Windows";
#else
    std::string platform = "Linux";
#endif

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    std::string screenSize = (QString::number(width) + "x" + QString::number(height)).toStdString();

    std::string productName = QSysInfo::prettyProductName().toStdString();
    std::string kernelVersion = QSysInfo::kernelVersion().split("-").first().toStdString();

    qDebug() << "Initializing Countly" << productName.c_str() << kernelVersion.c_str() << screenSize.c_str();

    Countly &ct = Countly::getInstance();
    // OS, OS_version, device, resolution, carrier, app_version);
    ct.SetMetrics(platform, kernelVersion, productName, screenSize, "", Vremenar::version.data());
    ct.setDeviceID(deviceId);
    ct.setSalt(Vremenar::CountlySalt.data());
    ct.Start(Vremenar::CountlyAppKey.data(), Vremenar::CountlyEndpoint.data());
}

void AnalyticsEngineCpp::beginSession() const
{
    Countly &ct = Countly::getInstance();
    ct.beginSession();
}

void AnalyticsEngineCpp::updateSession() const
{
    Countly &ct = Countly::getInstance();
    ct.updateSession();
}

void AnalyticsEngineCpp::endSession() const
{
    Countly &ct = Countly::getInstance();
    ct.endSession();
}

void AnalyticsEngineCpp::recordEvent(const QString &event) const
{
    Q_UNUSED(event)

    // Events not supported at the moment
    // Countly &ct = Countly::getInstance();
    // ct.RecordEvent(event.toStdString(), 1);
}

} // namespace Vremenar
