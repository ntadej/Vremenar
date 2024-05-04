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

#include "weather/containers/MapLegendItem.h"

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <utility>

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
      _color(color),
      _placeholder(placeholder)
{
    setId(Weather::mapTypeToString(type) + "_" + _value);
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
        return {};
    }

    return {};
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapLegendItem.cpp"
// NOLINTEND
