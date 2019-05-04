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

#include "weather/common/containers/MapInfo.h"

namespace Vremenar
{

MapInfo::MapInfo(Weather::MapType type,
                 QObject *parent)
    : ListItem(parent)
{
    _id = Weather::mapTypeString(type);
    _description = Weather::mapTypeStringLocale(type);
    _type = type;
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
        return QVariant();
    }
}

} // namespace Vremenar
