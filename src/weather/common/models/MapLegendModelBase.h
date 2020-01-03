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

#ifndef VREMENAR_MAPLEGENDMODELBASE_H_
#define VREMENAR_MAPLEGENDMODELBASE_H_

#include "common/ListModel.h"
#include "weather/common/containers/MapLegendItem.h"

namespace Vremenar
{

class MapLegendModelBase : public ListModel
{
    Q_OBJECT
public:
    explicit MapLegendModelBase(QObject *parent = nullptr);

protected:
    MapLegendItem *emplace(Weather::MapType type,
                           const QString &value,
                           const QColor &color,
                           bool placeholder = false);
};

} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDMODELBASE_H_
