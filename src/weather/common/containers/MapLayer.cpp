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

#include <QtCore/QLocale>

#include "weather/common/containers/MapLayer.h"

namespace Vremenar
{

MapLayer::MapLayer(Weather::MapType type,
                   Weather::MapRenderingType rendering,
                   Weather::ObservationType observation,
                   const QDateTime &time,
                   const QUrl &url,
                   const QGeoRectangle &bbox,
                   QObject *parent)
    : ListItem(parent)
{
    setId(Weather::mapTypeToString(type) + "_" + QString::number(time.toMSecsSinceEpoch()));

    _observation = observation;
    _type = type;
    _rendering = rendering;
    _time = time;
    _url = url;
    _bbox = bbox;
    _coordinates = geoRectangleToList(bbox);
}

QString MapLayer::display() const
{
    return QLocale::system().toString(_time.time(), QLocale::ShortFormat);
}

QVariant MapLayer::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case ObservationRole:
        return observation();
    case TypeRole:
        return type();
    case RenderingRole:
        return rendering();
    case TimeRole:
        return time();
    case TimestampRole:
        return time().toMSecsSinceEpoch();
    case UrlRole:
        return url();
    case MinLatitudeRole:
        return bbox().bottomLeft().latitude();
    case MinLongitudeRole:
        return bbox().bottomLeft().longitude();
    case MaxLatitudeRole:
        return bbox().topRight().latitude();
    case MaxLongitudeRole:
        return bbox().topRight().longitude();
    case CoordinatesRole:
        return coordinates();
    case LoadedRole:
        return loaded();
    default:
        return QVariant();
    }
}

void MapLayer::setBbox(const QGeoRectangle &bbox)
{
    _bbox = bbox;
}

void MapLayer::setLoaded()
{
    _loaded = true;
    Q_EMIT loadedChanged();
}

// clazy:excludeall=inefficient-qlist
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
