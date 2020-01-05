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

#ifndef VREMENAR_ARSOCURRENTWEATHER_H_
#define VREMENAR_ARSOCURRENTWEATHER_H_

#include "weather/common/CurrentWeatherBase.h"

namespace Vremenar
{
namespace ARSO
{

class CurrentWeather : public CurrentWeatherBase
{
    Q_OBJECT
public:
    explicit CurrentWeather(QObject *parent = nullptr);

    void updateCurrentWeather(const QJsonObject &data) final;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOCURRENTWEATHER_H_
