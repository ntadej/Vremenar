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

#include "weather/api/APIAlerts.h"

#include "weather/api/APIRequest.h"
#include "weather/api/APISources.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QUrlQuery>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

APIRequest API::alerts(const QStringList &alertsAreas)
{
    QUrlQuery query = sourceAndLocaleQuery();
    for (const QString &area : alertsAreas) {
        query.addQueryItem(u"area"_s, area);
    }

    APIRequest request;
    request.setCall(u"/alerts/list"_s);
    request.setUrl(u"/alerts/list"_s, query);

    return request;
}

} // namespace Vremenar
