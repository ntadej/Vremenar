/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/arso/api/ARSOAPIMapLayers.h"

namespace Vremenar
{

ARSO::APIRequest ARSO::mapLayers(Weather::MapType type)
{
    QString id;
    switch (type) {
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
    }

    APIRequest request;
    request.setCall(QStringLiteral("/inca_data"));
    request.setUrl("/" + id + "/");
    request.setExtra(type);

    return request;
}

} // namespace Vremenar
