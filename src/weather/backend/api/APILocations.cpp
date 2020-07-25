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

#include <QtCore/QUrlQuery>

#include "weather/backend/api/APILocations.h"

namespace Vremenar
{

Backend::APIRequest Backend::locations(const QGeoCoordinate &coordinate)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("lat"), QString::number(coordinate.latitude()));
    query.addQueryItem(QStringLiteral("lon"), QString::number(coordinate.longitude()));

    APIRequest request;
    request.setCall(QStringLiteral("/locations/coordinate"));
    request.setUrl(QStringLiteral("/locations/"), query);
    request.setExtra(coordinate.toString());

    return request;
}

Backend::APIRequest Backend::locations(const QString &location)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("loc"), location);

    APIRequest request;
    request.setCall(QStringLiteral("/locations/string"));
    request.setUrl(QStringLiteral("/locations/"), query);
    request.setExtra(location);

    return request;
}

} // namespace Vremenar
