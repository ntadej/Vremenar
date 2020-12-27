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

#include "common/ListModel.h"
#include "weather/containers/MapLegendItem.h"

namespace Vremenar
{

class MapLegendModel : public ListModel
{
    Q_OBJECT
public:
    explicit MapLegendModel(QObject *parent = nullptr);

    void addMapLegends(const QJsonArray &data);

private:
    MapLegendItem *emplace(Weather::MapType type,
                           const QString &value,
                           const QColor &color,
                           bool placeholder = false);
    QString translate(const QString &string);
};

} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDMODEL_H_
