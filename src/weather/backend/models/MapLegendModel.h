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

#ifndef VREMENAR_MAPLEGENDMODEL_H_
#define VREMENAR_MAPLEGENDMODEL_H_

#include "weather/common/models/MapLegendModelBase.h"

namespace Vremenar
{
namespace Backend
{

class MapLegendModel : public MapLegendModelBase
{
    Q_OBJECT
public:
    explicit MapLegendModel(QObject *parent = nullptr);
};

} // namespace Backend
} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDMODEL_H_
