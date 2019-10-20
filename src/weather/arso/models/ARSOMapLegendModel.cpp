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

#include "weather/arso/models/ARSOMapLegendModel.h"

namespace Vremenar
{

// clazy:excludeall=qcolor-from-literal

ARSO::MapLegendModel::MapLegendModel(QObject *parent)
    : MapLegendModelBase(parent)
{
    // Precipitation
    emplace(Weather::PrecipitationMap, QStringLiteral("0"), QColor("#00000000"));
    emplace(Weather::PrecipitationMap, QStringLiteral("15"), QColor("#3e67ff"));
    emplace(Weather::PrecipitationMap, QStringLiteral("18"), QColor("#3797ff"));
    emplace(Weather::PrecipitationMap, QStringLiteral("21"), QColor("#30c1f6"));
    emplace(Weather::PrecipitationMap, QStringLiteral("24"), QColor("#31e7fc"));
    emplace(Weather::PrecipitationMap, QStringLiteral("27"), QColor("#33d397"));
    emplace(Weather::PrecipitationMap, QStringLiteral("30"), QColor("#2fef28"));
    emplace(Weather::PrecipitationMap, QStringLiteral("33"), QColor("#8bfa36"));
    emplace(Weather::PrecipitationMap, QStringLiteral("36"), QColor("#c8fa33"));
    emplace(Weather::PrecipitationMap, QStringLiteral("39"), QColor("#f6fb2a"));
    emplace(Weather::PrecipitationMap, QStringLiteral("42"), QColor("#fed430"));
    emplace(Weather::PrecipitationMap, QStringLiteral("45"), QColor("#ff9a2c"));
    emplace(Weather::PrecipitationMap, QStringLiteral("48"), QColor("#fe6637"));
    emplace(Weather::PrecipitationMap, QStringLiteral("51"), QColor("#d42e38"));
    emplace(Weather::PrecipitationMap, QStringLiteral("54"), QColor("#b22923"));
    emplace(Weather::PrecipitationMap, QStringLiteral("57"), QColor("#d436d7"));
}

} // namespace Vremenar
