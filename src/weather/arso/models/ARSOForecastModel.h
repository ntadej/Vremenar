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

#ifndef VREMENAR_ARSOFORECASTMODEL_H_
#define VREMENAR_ARSOFORECASTMODEL_H_

#include "weather/common/models/ForecastModelBase.h"

namespace Vremenar
{
namespace ARSO
{

class ForecastModel : public ForecastModelBase
{
    Q_OBJECT
public:
    explicit ForecastModel(QObject *parent = nullptr);

    ForecastEntry *createEntry(const QJsonObject &data) final;
    void addEntries(const QJsonArray &data) final;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOFORECASTMODEL_H_
