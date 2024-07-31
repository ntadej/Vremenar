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

#include "maps/MapsCommon.h"

#include "common/containers/Hyperlink.h"

#include <QtCore/QString>

#include <memory>
#include <vector>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar::Maps
{

std::vector<std::unique_ptr<Hyperlink>> copyright()
{
    std::vector<std::unique_ptr<Hyperlink>> list;
    list.emplace_back(std::make_unique<Hyperlink>(
        u"© OpenMapTiles"_s,
        u"https://openmaptiles.org"_s));
    list.emplace_back(std::make_unique<Hyperlink>(
        u"© OpenStreetMap contributors"_s,
        u"https://www.openstreetmap.org/copyright"_s));
    list.emplace_back(std::make_unique<Hyperlink>(
        u"© Sentinel-2 cloudless by EOX IT Services GmbH (Contains modified Copernicus Sentinel data 2021)"_s,
        u"https://s2maps.eu"_s));
    return list;
}

} // namespace Vremenar::Maps
