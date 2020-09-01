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

#include "weather/backend/api/APIMapLayers.h"

#include "Config.h"

namespace Vremenar
{

Backend::APIRequest Backend::mapImage(const QString &url)
{
    APIRequest request;
    request.setBaseUrl(QString());
    request.setCall(QStringLiteral("/image"));
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

    return request;
}

Backend::APIRequest Backend::mapWeatherDetails(const QString &url)
{
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    APIRequest request;
    request.setCall(QStringLiteral("/weather_map"));
    request.setUrl(url, query);

    return request;
}

Backend::APIRequest Backend::mapLayers(Weather::MapType type)
{
    QString id;
    switch (type) {
    case Weather::WeatherConditionMap:
        id = QStringLiteral("condition");
        break;
    case Weather::PrecipitationMap:
        id = QStringLiteral("precipitation");
        break;
    case Weather::CloudCoverageMap:
        id = QStringLiteral("cloud");
        break;
    case Weather::WindSpeedMap:
        id = QStringLiteral("wind");
        break;
    case Weather::TemperatureMap:
        id = QStringLiteral("temperature");
        break;
    case Weather::HailProbabilityMap:
        id = QStringLiteral("hail");
        break;
    case Weather::UnknownMapType:
        throw std::runtime_error("unknown map");
    }

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("country"), QStringLiteral("si"));

    APIRequest request;
    request.setCall(QStringLiteral("/maps"));
    request.setUrl("/maps/" + id, query);
    request.setExtra(static_cast<int>(type));

    return request;
}

} // namespace Vremenar
