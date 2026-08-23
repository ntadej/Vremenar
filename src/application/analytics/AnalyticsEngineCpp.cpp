/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/analytics/AnalyticsEngineCpp.h"

#include "settings/Settings.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QSysInfo>
#include <QtCore/QUuid>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <memory>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

AnalyticsEngineCpp::AnalyticsEngineCpp(NetworkManager * /*network*/)
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
    const QString platform = u"Windows"_s;
#else
    const QString platform = u"Linux"_s;
#endif

    const QScreen *screen = QGuiApplication::primaryScreen();
    const QRect screenGeometry = screen->geometry();
    const int height = screenGeometry.height();
    const int width = screenGeometry.width();
    const QString screenSize = QString::number(width) + "x" + QString::number(height);

    const QString productName = QSysInfo::prettyProductName();
    const QString kernelVersion = QSysInfo::kernelVersion().split('-').first();

    // TODO(tadej): migrate
}

AnalyticsEngineCpp::~AnalyticsEngineCpp() = default;

void AnalyticsEngineCpp::beginSession() const
{
    // TODO(tadej): migrate
}

void AnalyticsEngineCpp::updateSession() const
{
    // TODO(tadej): migrate
}

void AnalyticsEngineCpp::endSession() const
{
    // TODO(tadej): migrate
}

void AnalyticsEngineCpp::recordEvent(const QString &event) const
{
    Q_UNUSED(event)

    // Events not supported at the moment
    // TODO(tadej): migrate
}

} // namespace Vremenar
