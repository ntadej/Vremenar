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

#include "maps/MapsCommon.h"

namespace Vremenar::Maps
{

std::vector<std::unique_ptr<Hyperlink>> copyright()
{
    std::vector<std::unique_ptr<Hyperlink>> list;
    list.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© OpenMapTiles"),
        QStringLiteral("https://openmaptiles.org")));
    list.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© OpenStreetMap contributors"),
        QStringLiteral("https://www.openstreetmap.org/copyright")));
    list.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© Sentinel-2 cloudless by EOX IT Services GmbH (Contains modified Copernicus Sentinel data 2017 & 2018)"),
        QStringLiteral("https://s2maps.eu")));
    return list;
}

} // namespace Vremenar::Maps
