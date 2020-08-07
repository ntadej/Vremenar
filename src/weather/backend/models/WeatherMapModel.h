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

#ifndef VREMENAR_WEATHERMAPMODEL_H_
#define VREMENAR_WEATHERMAPMODEL_H_

#include "weather/common/models/WeatherMapModelBase.h"

namespace Vremenar
{
namespace Backend
{

class WeatherMapModel : public WeatherMapModelBase
{
    Q_OBJECT
public:
    explicit WeatherMapModel(QObject *parent = nullptr);

    WeatherInfo *createEntry(const QJsonObject &data) final;
    void addEntries(const QJsonArray &data) final;
};

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_WEATHERMAPMODEL_H_
