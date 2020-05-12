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

#ifndef VREMENAR_FORECASTMODELBASE_H_
#define VREMENAR_FORECASTMODELBASE_H_

#include "common/ListModel.h"
#include "weather/common/containers/ForecastEntry.h"

namespace Vremenar
{

class ForecastModelBase : public ListModel
{
    Q_OBJECT
public:
    explicit ForecastModelBase(QObject *parent = nullptr);

    virtual ForecastEntry *createEntry(const QJsonObject &data) = 0;
    virtual void addEntries(const QJsonArray &data) = 0;

    void update(ForecastModelBase *model,
                qint64 time);
};

} // namespace Vremenar

#endif // VREMENAR_FORECASTMODELBASE_H_
