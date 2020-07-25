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

Backend::APIRequest Backend::mapForecast()
{
    APIRequest request;
    request.setCall(QStringLiteral("/forecast_data"));
    request.setUrl(QStringLiteral("/forecast_si_data/"));

    return request;
}

Backend::APIRequest Backend::mapForecastDetails(const QString &url)
{
    APIRequest request;
    request.setBaseUrl(Vremenar::ARSOAPIResources);
    request.setCall(QStringLiteral("/forecast_data_details"));
    request.setUrl(url);

    return request;
}

Backend::APIRequest Backend::mapLayers(Weather::MapType type)
{
    QString id;
    switch (type) {
    case Weather::ForecastMap:
        throw std::runtime_error("not supported");
    case Weather::PrecipitationMap:
        id = QStringLiteral("inca_precip_data");
        break;
    case Weather::CloudCoverageMap:
        id = QStringLiteral("inca_cloud_data");
        break;
    case Weather::WindSpeedMap:
        id = QStringLiteral("inca_wind_data");
        break;
    case Weather::TemperatureMap:
        id = QStringLiteral("inca_t2m_data");
        break;
    case Weather::HailProbabilityMap:
        id = QStringLiteral("inca_hail_data");
        break;
    case Weather::UnknownMap:
        throw std::runtime_error("unknown map");
    }

    APIRequest request;
    request.setCall(QStringLiteral("/inca_data"));
    request.setUrl("/" + id + "/");
    request.setExtra(type);

    return request;
}

} // namespace Vremenar