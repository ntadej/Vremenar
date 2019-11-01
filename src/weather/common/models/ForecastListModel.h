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

#ifndef VREMENAR_FORECASTLISTMODEL_H_
#define VREMENAR_FORECASTLISTMODEL_H_

#include "common/ListModel.h"
#include "weather/common/containers/ForecastInfo.h"

namespace Vremenar
{

class ForecastListModel : public ListModel
{
    Q_OBJECT
public:
    explicit ForecastListModel(QObject *parent = nullptr);

    void generateModel(const QJsonArray &array);

    inline ForecastInfo *get(int index) { return row<ForecastInfo>(index); }
};

} // namespace Vremenar

#endif // VREMENAR_FORECASTLISTMODEL_H_
