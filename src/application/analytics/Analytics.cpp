/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/analytics/Analytics.h"

#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
#include "application/analytics/AnalyticsEngineMacOSiOS.h"
#elif defined(Q_OS_ANDROID)
#include "application/analytics/AnalyticsEngineAndroid.h"
#endif

namespace Vremenar
{

Analytics::Analytics(QObject *parent)
    : QObject(parent)
{
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    _engine = std::make_unique<AnalyticsEngineMacOSiOS>();
#elif defined(Q_OS_ANDROID)
    _engine = std::make_unique<AnalyticsEngineAndroid>();
#endif
}

QString Analytics::eventString(EventType type,
                               const QString &payload)
{
    QString string;
    switch (type) {
    case MapTypeChanged:
        string = QStringLiteral("map_changed");
        break;
    }

    if (!payload.isEmpty()) {
        string.append(QStringLiteral("_")).append(payload);
    }

    return string;
}

void Analytics::recordEvent(EventType type,
                            const QString &payload) const
{
    if (_engine == nullptr) {
        return;
    }

    QString event = eventString(type, payload);
    _engine->recordEvent(event);
}

} // namespace Vremenar
