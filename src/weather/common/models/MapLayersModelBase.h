/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPLAYERSMODELBASE_H_
#define VREMENAR_MAPLAYERSMODELBASE_H_

#include "common/ListModel.h"
#include "weather/common/containers/MapLayer.h"

namespace Vremenar
{

class MapLayersModelBase : public ListModel
{
    Q_OBJECT
public:
    explicit MapLayersModelBase(QObject *parent = nullptr);

    MapLayer *find(const QString &id) const;
    MapLayer *row(int row);
    std::unique_ptr<MapLayer> takeRow(int row);

    virtual MapLayer *createMapLayer(Weather::MapType type,
                                     const QJsonObject &data)
        = 0;
    void deleteMapLayer(MapLayer *genre);

    virtual void addMapLayers(Weather::MapType type,
                              const QJsonArray &data)
        = 0;
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYERSMODELBASE_H_