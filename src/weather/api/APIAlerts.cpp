/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/Sources.h"

#include "weather/api/APIAlerts.h"

namespace Vremenar
{

APIRequest API::alerts(const QStringList &alertsAreas)
{
    QUrlQuery query = Sources::sourceAndLocaleQuery();
    for (const QString &area : alertsAreas) {
        query.addQueryItem(QStringLiteral("area"), area);
    }

    APIRequest request;
    request.setCall(QStringLiteral("/alerts/list"));
    request.setUrl(QStringLiteral("/alerts/list"), query);

    return request;
}

} // namespace Vremenar
