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

#include "weather/common/containers/MapLayer.h"

namespace Vremenar
{

MapLayer::MapLayer(Weather::MapType type,
                   const QDateTime &time,
                   const QUrl &url,
                   const QGeoRectangle &range,
                   QObject *parent)
    : ListItem(parent)
{
    _id = Weather::mapTypeString(type) + "_" + QString::number(time.toSecsSinceEpoch());
    _type = type;
    _time = time;
    _url = url;
    _range = range;
    _coordinates = geoRectangleToList(range);
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
        return time().toMSecsSinceEpoch();
    case UrlRole:
        return url();
    case MinLatitudeRole:
        return range().bottomLeft().latitude();
    case MinLongitudeRole:
        return range().bottomLeft().longitude();
    case MaxLatitudeRole:
        return range().topRight().latitude();
    case MaxLongitudeRole:
        return range().topRight().longitude();
    case CoordinatesRole:
        return coordinates();
    default:
        return QVariant();
    }
}

QVariant MapLayer::geoRectangleToList(const QGeoRectangle &rect)
{
    QVariantList list{
        QVariant::fromValue(QVariantList({QVariant(rect.topLeft().latitude()), QVariant(rect.topLeft().longitude())})),
        QVariant::fromValue(QVariantList({QVariant(rect.bottomRight().latitude()), QVariant(rect.topLeft().longitude())})),
        QVariant::fromValue(QVariantList({QVariant(rect.bottomRight().latitude()), QVariant(rect.bottomRight().longitude())})),
        QVariant::fromValue(QVariantList({QVariant(rect.topLeft().latitude()), QVariant(rect.bottomRight().longitude())}))};
    return QVariant::fromValue(list);
}

} // namespace Vremenar
