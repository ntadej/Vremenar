/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPINFOMODEL_H_
#define VREMENAR_MAPINFOMODEL_H_

#include "common/ListModel.h"
#include "weather/common/containers/MapInfo.h"

namespace Vremenar
{

class MapInfoModel : public ListModel
{
    Q_OBJECT
public:
    explicit MapInfoModel(QObject *parent = nullptr);
    virtual ~MapInfoModel() = default;

    void generateModel(const std::vector<Weather::MapType> &supported);
};

} // namespace Vremenar

#endif // VREMENAR_MAPINFOMODEL_H_
