/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/containers/MapLayer.h"

namespace Vremenar
{

MapLayer::MapLayer(QObject *parent)
    : ListItem(parent)
{
    generateRoleNames();

    _id = "prototype";
    _type = Weather::PrecipitationMap;
}

MapLayer::MapLayer(Weather::MapType type,
                   const QDateTime &time,
                   const QUrl &url,
                   const QGeoRectangle &range,
                   QObject *parent)
    : ListItem(parent)
{
    generateRoleNames();

    _id = Weather::mapTypeString(type) + "_" + QString::number(time.toSecsSinceEpoch());
    _type = type;
    _time = time;
    _url = url;
    _range = range;
}

void MapLayer::generateRoleNames()
{
    _roleNames[IdRole] = "id";
    _roleNames[DisplayRole] = "display";
    _roleNames[TypeRole] = "type";
    _roleNames[TimeRole] = "time";
    _roleNames[TimestampRole] = "timestamp";
    _roleNames[UrlRole] = "url";
    _roleNames[MinLatitude] = "minLatitude";
    _roleNames[MinLongitude] = "minLongitude";
    _roleNames[MaxLatitude] = "maxLatitude";
    _roleNames[MaxLongitude] = "maxLongitude";
}

QString MapLayer::display() const
{
    return _time.time().toString(Qt::SystemLocaleShortDate);
}

QVariant MapLayer::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case TypeRole:
        return type();
    case TimeRole:
        return time();
    case TimestampRole:
        return time().toSecsSinceEpoch();
    case UrlRole:
        return url();
    case MinLatitude:
        return range().bottomLeft().latitude();
    case MinLongitude:
        return range().bottomLeft().longitude();
    case MaxLatitude:
        return range().topRight().latitude();
    case MaxLongitude:
        return range().topRight().longitude();
    default:
        return QVariant();
    }
}

} // namespace Vremenar
