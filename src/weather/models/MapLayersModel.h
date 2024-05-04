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

#ifndef VREMENAR_MAPLAYERSMODEL_H_
#define VREMENAR_MAPLAYERSMODEL_H_

#include "common/ListModel.h"
#include "weather/Weather.h"

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtPositioning/QGeoRectangle>

namespace Vremenar
{

class MapLayer;

class MapLayersModel : public ListModel
{
    Q_OBJECT
public:
    explicit MapLayersModel(QObject *parent = nullptr);

    MapLayer *createMapLayer(Weather::MapType type,
                             Weather::MapRenderingType rendering,
                             const QJsonObject &data,
                             const QGeoRectangle &bbox);

    void addMapLayers(Weather::MapType type,
                      const QJsonObject &data);

    [[nodiscard]] MapLayer *findLayer(Weather::MapType type,
                                      qint64 time) const;
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYERSMODEL_H_
