/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <stdexcept>

#include "weather/Sources.h"

#include "weather/api/APIMapLayers.h"

#include "Config.h"

namespace Vremenar
{

APIRequest API::mapLayers(Weather::MapType type)
{
    if (type == Weather::UnknownMapType) {
        throw std::runtime_error("unknown map");
    }

    const QString id = Weather::mapTypeToString(type);
    const QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/maps/list"));
    request.setUrl("/maps/list/" + id, query);
    request.setExtra(static_cast<int>(type));

    return request;
}

APIRequest API::mapLegends()
{
    const QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/maps/legend"));
    request.setUrl(QStringLiteral("/maps/legend"), query);

    return request;
}

APIRequest API::mapTypes()
{
    const QUrlQuery query = Sources::sourceQuery();

    APIRequest request;
    request.setCall(QStringLiteral("/maps/types"));
    request.setUrl(QStringLiteral("/maps/types"), query);

    return request;
}

} // namespace Vremenar
