/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_WEATHERMAPMODEL_H_
#define VREMENAR_WEATHERMAPMODEL_H_

#include "common/ListModel.h"
#include "weather/containers/WeatherInfo.h"

namespace Vremenar
{

class StationListModel;

class WeatherMapModel : public ListModel
{
    Q_OBJECT
public:
    explicit WeatherMapModel(QObject *parent = nullptr);

    void addEntries(StationListModel *stations,
                    const QJsonArray &data);
    void update(WeatherMapModel *model,
                qint64 time);
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERMAPMODELBASE_H_
