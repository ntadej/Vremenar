/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/arso/api/ARSOAPIMapLayers.h"

namespace Vremenar
{

ARSO::APIRequest ARSO::mapLayers(Weather::MapType type)
{
    QString id;
    switch (type) {
    case Weather::PrecipitationMap:
        id = "inca_precip_data";
        break;
    case Weather::CloudCoverageMap:
        id = "inca_cloud_data";
        break;
    case Weather::WindSpeedMap:
        id = "inca_wind_data";
        break;
    case Weather::TemperatureMap:
        id = "inca_t2m_data";
        break;
    case Weather::HailProbabilityMap:
        id = "inca_hail_data";
        break;
    }

    APIRequest request;
    request.setCall("/inca_data");
    request.setUrl("/" + id + "/");
    request.setExtra(type);

    return request;
}

} // namespace Vremenar
