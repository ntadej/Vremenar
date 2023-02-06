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

#include "weather/containers/MapLegendItem.h"

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
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
      _color(color),
#else
      _color(std::move(color)),
#endif
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
    }

    return {};
}

} // namespace Vremenar

#include "moc_MapLegendItem.cpp"
