/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "weather/arso/api/ARSOAPICommon.h"
#include "weather/arso/models/ARSOMapLayersModel.h"

ARSOMapLayersModel::ARSOMapLayersModel(QObject *parent)
    : MapLayersModel(parent) {}

ARSOMapLayersModel::~ARSOMapLayersModel() {}

MapLayer *ARSOMapLayersModel::createMapLayer(Vremenar::Weather::MapType type,
                                             const QJsonObject &data)
{
    QDateTime time = QDateTime::fromString(data["date"].toString(), "yyyyMMddHHmm");
    time.setTimeSpec(Qt::UTC);

    QUrl url(Vremenar::ARSO::baseUrl() + data["path"].toString());

    QStringList c = data["bbox"].toString().split(",");
    QGeoCoordinate topLeft(c[2].toDouble(), c[1].toDouble());
    QGeoCoordinate bottomRight(c[0].toDouble(), c[3].toDouble());
    QGeoRectangle range(topLeft, bottomRight);

    MapLayer *layer = new MapLayer(type, time, url, range);
    appendRow(layer);

    return row(indexFromItem(layer).row());
}

void ARSOMapLayersModel::addMapLayers(Vremenar::Weather::MapType type,
                                      const QJsonArray &data)
{
    for (int i = 0; i < data.size(); i++) {
        createMapLayer(type, data[i].toObject());
    }
}
