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

#ifndef VREMENAR_ARSOMAPLEGENDMODEL_H_
#define VREMENAR_ARSOMAPLEGENDMODEL_H_

#include "weather/common/models/MapLegendModelBase.h"

namespace Vremenar
{
namespace ARSO
{

class MapLegendModel : public MapLegendModelBase
{
    Q_OBJECT
public:
    explicit MapLegendModel(QObject *parent = nullptr);
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOMAPLEGENDMODEL_H_