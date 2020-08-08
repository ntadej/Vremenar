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

#include <QtCore/QJsonDocument>
#include <QtCore/QUrlQuery>

#include "weather/backend/api/APILocations.h"

namespace Vremenar
{

Backend::APIRequest Backend::locations(const QGeoCoordinate &coordinate)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    QJsonObject data;
    data[QStringLiteral("latitude")] = coordinate.latitude();
    data[QStringLiteral("longitude")] = coordinate.longitude();

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(QStringLiteral("/location/coordinate"));
    request.setUrl(QStringLiteral("/location/find"), query);
    request.setData(data);
    request.setExtra(coordinate.toString());

    return request;
}

Backend::APIRequest Backend::locations(const QString &location)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    QJsonObject data;
    data[QStringLiteral("string")] = location;

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(QStringLiteral("/location/string"));
    request.setUrl(QStringLiteral("/location/find"), query);
    request.setData(data);
    request.setExtra(location);

    return request;
}

} // namespace Vremenar
