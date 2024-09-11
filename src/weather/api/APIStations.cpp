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

#include "weather/api/APIStations.h"

#include "weather/api/APIRequest.h"
#include "weather/api/APISources.h"

#include <QtCore/QJsonObject>
#include <QtCore/QString>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtPositioning/QGeoCoordinate>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

APIRequest API::stations(const QGeoCoordinate &coordinate)
{
    QUrlQuery query = sourceQuery();
    query.addQueryItem(u"include_forecast_only"_s, u"true"_s);

    QJsonObject data;
    data[u"latitude"_s] = coordinate.latitude();
    data[u"longitude"_s] = coordinate.longitude();

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(u"/stations/coordinate"_s);
    request.setUrl(u"/stations/find"_s, query);
    request.setData(data);
    request.setExtra(coordinate.toString());

    return request;
}

APIRequest API::stations(const QString &string)
{
    QUrlQuery query = sourceQuery();
    query.addQueryItem(u"include_forecast_only"_s, u"true"_s);

    QJsonObject data;
    data[u"string"_s] = string;

    APIRequest request;
    request.setOperation(QNetworkAccessManager::PostOperation);
    request.setCall(u"/stations/string"_s);
    request.setUrl(u"/stations/find"_s, query);
    request.setData(data);
    request.setExtra(string);

    return request;
}

APIRequest API::stationWeatherCondition(const QString &id)
{
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/stations/condition"_s);
    request.setUrl("/stations/condition/" + id, query);
    request.setExtra(id);

    return request;
}

APIRequest API::stationsList()
{
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/stations/list"_s);
    request.setUrl(u"/stations/list"_s, query);

    return request;
}

APIRequest API::stationsMap(const QString &url)
{
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/stations/map"_s);
    request.setUrl(url, query);

    return request;
}

} // namespace Vremenar
