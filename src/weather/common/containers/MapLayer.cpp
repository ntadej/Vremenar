/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/containers/MapLayer.h"

MapLayer::MapLayer(QObject *parent)
    : ListItem(parent) {}

MapLayer::MapLayer(Vremenar::Weather::MapType type,
                   const QDateTime &time,
                   const QUrl &url,
                   const QGeoRectangle &range,
                   QObject *parent)
    : ListItem(parent)
{
    _type = type;
    _time = time;
    _url = url;
    _range = range;
}

MapLayer::~MapLayer() {}

QString MapLayer::id() const
{
    return Vremenar::Weather::mapTypeString(_type) + "_" + QString::number(_time.toSecsSinceEpoch());
}

QString MapLayer::display() const
{
    return _time.time().toString(Qt::SystemLocaleShortDate);
}

QHash<int, QByteArray> MapLayer::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IdRole] = "id";
    names[DisplayRole] = "display";
    names[TypeRole] = "type";
    names[TimeRole] = "time";
    names[UrlRole] = "url";
    return names;
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
    case UrlRole:
        return url();
    default:
        return QVariant();
    }
}
