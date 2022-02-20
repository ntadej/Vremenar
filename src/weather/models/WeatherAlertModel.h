/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_WEATHERALERTMODEL_H_
#define VREMENAR_WEATHERALERTMODEL_H_

#include <memory>

#include "common/ListModel.h"
#include "weather/containers/WeatherAlert.h"

namespace Vremenar
{

class WeatherAlertModel : public ListModel
{
    Q_OBJECT
public:
    explicit WeatherAlertModel(QObject *parent = nullptr);

    void update(std::vector<std::unique_ptr<WeatherAlert>> &list);
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERALERTMODEL_H_
