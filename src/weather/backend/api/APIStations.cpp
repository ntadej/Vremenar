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

#include "weather/backend/api/APIStations.h"

namespace Vremenar
{

Backend::APIRequest Backend::stations(const QGeoCoordinate &coordinate)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    QJsonObject data;
    data[QStringLiteral("latitude")] = coordinate.latitude();
    data[QStringLiteral("longitude")] = coordinate.longitude();

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(QStringLiteral("/stations/coordinate"));
    request.setUrl(QStringLiteral("/stations/find"), query);
    request.setData(data);
    request.setExtra(coordinate.toString());

    return request;
}

Backend::APIRequest Backend::stations(const QString &string)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    QJsonObject data;
    data[QStringLiteral("string")] = string;

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(QStringLiteral("/stations/string"));
    request.setUrl(QStringLiteral("/stations/find"), query);
    request.setData(data);
    request.setExtra(string);

    return request;
}

Backend::APIRequest Backend::stationsMap(const QString &url)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("de"));

    APIRequest request;
    request.setCall(QStringLiteral("/stations/map"));
    request.setUrl(url, query);

    return request;
}

} // namespace Vremenar
