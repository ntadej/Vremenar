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

#include "weather/api/APIMapLayers.h"

#include "weather/Weather.h"
#include "weather/api/APIRequest.h"
#include "weather/api/APISources.h"

#include <QtCore/QString>
#include <QtCore/QUrlQuery>

#include <stdexcept>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

APIRequest API::mapLayers(Weather::MapType type)
{
    if (type == Weather::UnknownMapType) {
        throw std::runtime_error("unknown map");
    }

    const QString id = Weather::mapTypeToString(type);
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/maps/list"_s);
    request.setUrl("/maps/list/" + id, query);
    request.setExtra(static_cast<int>(type));

    return request;
}

APIRequest API::mapLegends()
{
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/maps/legend"_s);
    request.setUrl(u"/maps/legend"_s, query);

    return request;
}

APIRequest API::mapTypes()
{
    const QUrlQuery query = sourceQuery();

    APIRequest request;
    request.setCall(u"/maps/types"_s);
    request.setUrl(u"/maps/types"_s, query);

    return request;
}

} // namespace Vremenar
