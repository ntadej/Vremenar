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

#include "application/analytics/Analytics.h"
#include "application/analytics/AnalyticsEngine.h"

#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
#include "application/analytics/AnalyticsEngineMacOSiOS.h"
#elif defined(Q_OS_ANDROID)
#include "application/analytics/AnalyticsEngineAndroid.h"
#elif defined(Q_OS_LINUX) || defined(Q_OS_WINDOWS)
#include "application/analytics/AnalyticsEngineCpp.h"
#endif

#include <QtCore/QDebug>
#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include <memory>

using Qt::Literals::StringLiterals::operator""_L1;

namespace
{
constexpr int updateInterval{60000};
} // namespace

namespace Vremenar
{

Analytics::Analytics(NetworkManager *network,
                     QObject *parent)
    : QObject(parent),
      _timer(std::make_unique<QTimer>(this))
{
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    Q_UNUSED(network)
    _engine = std::make_unique<AnalyticsEngineMacOSiOS>();
#elif defined(Q_OS_ANDROID)
    Q_UNUSED(network)
    _engine = std::make_unique<AnalyticsEngineAndroid>();
#elif defined(Q_OS_LINUX) || defined(Q_OS_WINDOWS)
    _engine = std::make_unique<AnalyticsEngineCpp>(network);
#endif

    _timer->setInterval(updateInterval);
    _timer->setSingleShot(true);

    if (_engine->manualSessionHandling()) {
        connect(_timer.get(), &QTimer::timeout, this, &Analytics::updateSession);
    }
}

Analytics::~Analytics() = default;

void Analytics::beginSession()
{
    if (!_engine->manualSessionHandling()) {
        return;
    }

    _timer->stop();

    qDebug() << "Analytics: Begin session";

    _engine->beginSession();

    _timer->start();
}

void Analytics::updateSession()
{
    if (!_engine->manualSessionHandling()) {
        return;
    }

    _timer->stop();

    qDebug() << "Analytics: Update session";

    _engine->updateSession();

    _timer->start();
}

void Analytics::endSession()
{
    if (!_engine->manualSessionHandling()) {
        return;
    }

    _timer->stop();

    qDebug() << "Analytics: End session";

    _engine->endSession();
}

QString Analytics::eventString(EventType type,
                               const QString &payload)
{
    QString string;
    switch (type) {
    case MapStyleChanged:
        string.append("map_style_changed"_L1);
        break;
    case MapTypeChanged:
        string.append("map_changed"_L1);
        break;
    }

    if (!payload.isEmpty()) {
        string.append("_"_L1).append(payload);
    }

    return string;
}

void Analytics::recordEvent(EventType type,
                            const QString &payload) const
{
    if (_engine == nullptr) {
        return;
    }

    const QString event = eventString(type, payload);
    _engine->recordEvent(event);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Analytics.cpp"
// NOLINTEND
