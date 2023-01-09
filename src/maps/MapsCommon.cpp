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

#include "maps/MapsCommon.h"

#include "Config.h"

namespace Vremenar::Maps
{

std::vector<std::unique_ptr<Hyperlink>> copyright()
{
    bool selfHosted = !QString(Vremenar::mapsEndpoint).contains(QStringLiteral("maptiler"));

    std::vector<std::unique_ptr<Hyperlink>> list;
    if (selfHosted) {
        list.emplace_back(std::make_unique<Hyperlink>(
            QStringLiteral("© OpenMapTiles"),
            QStringLiteral("https://openmaptiles.org")));
    } else {
        list.emplace_back(std::make_unique<Hyperlink>(
            QStringLiteral("© MapTiler"),
            QStringLiteral("https://www.maptiler.com/copyright/")));
    }
    list.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© OpenStreetMap contributors"),
        QStringLiteral("https://www.openstreetmap.org/copyright")));
    if (selfHosted) {
        list.emplace_back(std::make_unique<Hyperlink>(
            QStringLiteral("© Sentinel-2 cloudless by EOX IT Services GmbH (Contains modified Copernicus Sentinel data 2021)"),
            QStringLiteral("https://s2maps.eu")));
    }
    return list;
}

} // namespace Vremenar::Maps
