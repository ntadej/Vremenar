/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/arso/api/ARSOAPIMapLayers.h"

ARSOAPIRequest Vremenar::ARSO::mapLayers(Vremenar::Weather::MapType type)
{
    QString id;
    switch (type) {
    case Vremenar::Weather::PrecipitationMap:
        id = "inca_precip_data";
        break;
    case Vremenar::Weather::CloudCoverageMap:
        id = "inca_precip_data";
        break;
    case Vremenar::Weather::WindSpeedMap:
        id = "inca_precip_data";
        break;
    case Vremenar::Weather::TemperatureMap:
        id = "inca_precip_data";
        break;
    case Vremenar::Weather::HailProbabilityMap:
        id = "inca_precip_data";
        break;
    default:
        break;
    }

    ARSOAPIRequest request;
    request.setCall("/inca_data");
    request.setUrl("/" + id + "/");
    request.setOperation(QNetworkAccessManager::GetOperation);
    request.setExtra(type);

    return request;
}
