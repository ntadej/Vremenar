/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOMAPLAYERSMODEL_H_
#define VREMENAR_ARSOMAPLAYERSMODEL_H_

#include "weather/common/models/MapLayersModel.h"

class ARSOMapLayersModel : public Vremenar::MapLayersModel
{
    Q_OBJECT
public:
    explicit ARSOMapLayersModel(QObject *parent = nullptr);
    virtual ~ARSOMapLayersModel();

    Vremenar::MapLayer *createMapLayer(Vremenar::Weather::MapType type,
                                       const QJsonObject &data) override;

    void addMapLayers(Vremenar::Weather::MapType type,
                      const QJsonArray &data) override;
};

#endif // VREMENAR_ARSOMAPLAYERSMODEL_H_
