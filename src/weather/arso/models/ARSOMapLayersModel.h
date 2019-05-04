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

#ifndef VREMENAR_ARSOMAPLAYERSMODEL_H_
#define VREMENAR_ARSOMAPLAYERSMODEL_H_

#include "weather/common/models/MapLayersModelBase.h"

namespace Vremenar
{
namespace ARSO
{

class MapLayersModel : public MapLayersModelBase
{
    Q_OBJECT
public:
    explicit MapLayersModel(QObject *parent = nullptr);

    MapLayer *createMapLayer(Weather::MapType type,
                             const QJsonObject &data) final;

    void addMapLayers(Weather::MapType type,
                      const QJsonArray &data) final;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOMAPLAYERSMODEL_H_
