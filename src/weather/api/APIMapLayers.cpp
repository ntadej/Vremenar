/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/Sources.h"

#include "weather/api/APIMapLayers.h"

#include "Config.h"

namespace Vremenar
{

APIRequest API::mapImage(const QString &url)
{
    APIRequest request;
    request.setBaseUrl(QString());
    request.setCall(QStringLiteral("/image"));
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

    return request;
}

APIRequest API::mapLayers(Weather::MapType type)
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

    QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/maps/list"));
    request.setUrl("/maps/list/" + id, query);
    request.setExtra(static_cast<int>(type));

    return request;
}

APIRequest API::mapLegends()
{
    QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/maps/legend"));
    request.setUrl(QStringLiteral("/maps/legend"), query);

    return request;
}

} // namespace Vremenar
