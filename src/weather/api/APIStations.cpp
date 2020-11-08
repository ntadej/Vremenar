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

#include "weather/Sources.h"

#include "weather/api/APIStations.h"

namespace Vremenar
{

APIRequest API::stations(const QGeoCoordinate &coordinate)
{
    QUrlQuery query = Sources::sourceQuery();

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

APIRequest API::stations(const QString &string)
{
    QUrlQuery query = Sources::sourceQuery();

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

APIRequest API::stationsMap(const QString &url)
{
    QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/stations/map"));
    request.setUrl(url, query);

    return request;
}

} // namespace Vremenar
