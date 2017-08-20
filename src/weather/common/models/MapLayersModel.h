/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPLAYERSMODEL_H_
#define VREMENAR_MAPLAYERSMODEL_H_

#include "common/ListModel.h"
#include "weather/common/containers/MapLayer.h"

class MapLayersModel : public ListModel
{
    Q_OBJECT
public:
    explicit MapLayersModel(QObject *parent = nullptr);
    virtual ~MapLayersModel();

    MapLayer *find(const QString &id) const;
    MapLayer *row(int row);
    MapLayer *takeRow(int row);

    virtual MapLayer *createMapLayer(Vremenar::Weather::MapType type,
                                     const QJsonObject &data)
        = 0;
    void deleteMapLayer(MapLayer *genre);

    virtual void addMapLayers(Vremenar::Weather::MapType type,
                              const QJsonArray &data)
        = 0;
};

#endif // VREMENAR_MAPLAYERSMODEL_H_
