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

#include "weather/containers/MapInfo.h"

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

namespace Vremenar
{

MapInfo::MapInfo(Weather::MapType type,
                 QObject *parent)
    : ListItem(parent),
      _type(type),
      _description(Weather::mapTypeToLocalizedString(type))
{
    setId(Weather::mapTypeToString(type));
}

QString MapInfo::display() const
{
    return _description;
}

QVariant MapInfo::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case TypeRole:
        return type();
    default:
        return {};
    }

    return {};
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_MapInfo.cpp"
// NOLINTEND
