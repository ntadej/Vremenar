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

#include "weather/models/MapLegendModelBase.h"

namespace Vremenar
{

MapLegendModelBase::MapLegendModelBase(QObject *parent)
    : ListModel(MapLegendItem::roleNames(), parent) {}

MapLegendItem *MapLegendModelBase::emplace(Weather::MapType type,
                                           const QString &value,
                                           const QColor &color,
                                           bool placeholder)
{
    auto item = std::make_unique<MapLegendItem>(type, value, color, placeholder);
    return appendRow(std::move(item));
}

} // namespace Vremenar
