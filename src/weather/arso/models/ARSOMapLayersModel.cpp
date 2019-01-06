/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtPositioning/QGeoCoordinate>

#include "common/Helpers.h"

#include "weather/arso/api/ARSOAPICommon.h"

#include "weather/arso/models/ARSOMapLayersModel.h"

namespace Vremenar
{

ARSO::MapLayersModel::MapLayersModel(QObject *parent)
    : MapLayersModelBase(parent) {}

MapLayer *ARSO::MapLayersModel::createMapLayer(Weather::MapType type,
                                               const QJsonObject &data)
{
    QDateTime time = QDateTime::fromString(data["date"].toString(), "yyyyMMddHHmm");
    time.setTimeSpec(Qt::UTC);

    QUrl url(ARSO::baseUrl() + data["path"].toString());

    QStringList c = data["bbox"].toString().split(",");
    QGeoCoordinate topLeft(c[2].toDouble(), c[1].toDouble());
    QGeoCoordinate bottomRight(c[0].toDouble(), c[3].toDouble());
    QGeoRectangle range(topLeft, bottomRight);

    auto layerPtr = std::make_unique<MapLayer>(type, time, url, range);
    return dynamic_cast<MapLayer *>(appendRow(qobject_pointer_cast<ListItem>(layerPtr.release())));
}

void ARSO::MapLayersModel::addMapLayers(Weather::MapType type,
                                        const QJsonArray &data)
{
    for (const QJsonValue &obj : data) {
        createMapLayer(type, obj.toObject());
    }
}

} // namespace Vremenar
