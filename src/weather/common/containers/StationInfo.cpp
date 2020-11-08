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

#include "weather/common/containers/StationInfo.h"

namespace Vremenar
{

StationInfo::StationInfo(const QString &id,
                         QString name,
                         const QGeoCoordinate &coordinate,
                         qreal zoomLevel,
                         QObject *parent)
    : ListItem(parent),
      _name(std::move(name)),
      _coordinate(coordinate),
      _zoomLevel(zoomLevel)
{
    setId(id);
}

std::unique_ptr<StationInfo> StationInfo::fromJson(const QJsonObject &json)
{
    QString id = json[QStringLiteral("id")].toString();
    QString name = json[QStringLiteral("name")].toString();

    QJsonObject coordinateObj = json[QStringLiteral("coordinate")].toObject();
    QGeoCoordinate coordinate{coordinateObj[QStringLiteral("latitude")].toDouble(), coordinateObj[QStringLiteral("longitude")].toDouble()};

    qreal zoomLevel = json[QStringLiteral("zoom_level")].toDouble();

    return std::make_unique<StationInfo>(id, name, coordinate, zoomLevel);
}

QString StationInfo::display() const
{
    return _name;
}

QVariant StationInfo::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case CoordinateRole:
        return QVariant::fromValue(coordinate());
    case ZoomLevelRole:
        return zoomLevel();
    }

    return QVariant();
}

} // namespace Vremenar
