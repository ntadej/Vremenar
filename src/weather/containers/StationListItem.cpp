/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/containers/StationListItem.h"

namespace Vremenar
{

StationListItem::StationListItem(const QString &id,
                                 QString name,
                                 const QGeoCoordinate &coordinate,
                                 QObject *parent)
    : ListItem(parent),
      _name(std::move(name)),
      _coordinate(coordinate)
{
    setId(id);
}

std::unique_ptr<StationListItem> StationListItem::fromJson(const QJsonObject &json)
{
    QString id = json[QStringLiteral("id")].toString();
    QString name = json[QStringLiteral("name")].toString();

    QJsonObject coordinateObj = json[QStringLiteral("coordinate")].toObject();
    QGeoCoordinate coordinate{coordinateObj[QStringLiteral("latitude")].toDouble(), coordinateObj[QStringLiteral("longitude")].toDouble()};

    return std::make_unique<StationListItem>(id, name, coordinate);
}

QString StationListItem::display() const
{
    return _name;
}

QVariant StationListItem::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
    case EditRole:
        return display();
    case CoordinateRole:
        return QVariant::fromValue(coordinate());
    }

    return QVariant();
}

} // namespace Vremenar
