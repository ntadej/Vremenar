/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_FORECASTMODEL_H_
#define VREMENAR_FORECASTMODEL_H_

#include "weather/common/models/ForecastModelBase.h"

namespace Vremenar
{
namespace Backend
{

class ForecastModel : public ForecastModelBase
{
    Q_OBJECT
public:
    explicit ForecastModel(QObject *parent = nullptr);

    ForecastEntry *createEntry(const QJsonObject &data) final;
    void addEntries(const QJsonArray &data) final;
};

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_FORECASTMODEL_H_
