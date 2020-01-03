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

#include "weather/common/containers/MapLegendItem.h"

namespace Vremenar
{

MapLegendItem::MapLegendItem(Weather::MapType type,
                             QString value,
                             QColor color,
                             bool placeholder,
                             QObject *parent)
    : ListItem(parent),
      _type(type),
      _value(std::move(value)),
      _color(std::move(color)),
      _placeholder(placeholder)
{
    setId(Weather::mapTypeString(type) + "_" + value);
}

QString MapLegendItem::display() const
{
    return _value;
}

QVariant MapLegendItem::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case TypeRole:
        return type();
    case ColorRole:
        return color();
    case PlaceholderRole:
        return placeholder();
    default:
        return QVariant();
    }
}

} // namespace Vremenar
