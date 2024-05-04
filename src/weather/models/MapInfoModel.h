/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_MAPINFOMODEL_H_
#define VREMENAR_MAPINFOMODEL_H_

#include "common/ListModel.h"
#include "weather/Weather.h"

#include <QtCore/QJsonArray>
#include <QtCore/QObject>
#include <QtCore/QStringList>

#include <vector>

namespace Vremenar
{

class MapInfoModel : public ListModel
{
    Q_OBJECT
public:
    explicit MapInfoModel(QObject *parent = nullptr);

    void generateModel(const std::vector<Weather::MapType> &supported);
    void generateModel(const QJsonArray &supported);

    [[nodiscard]] QStringList list() const;
    [[nodiscard]] std::vector<Weather::MapType> types() const;
};

} // namespace Vremenar

#endif // VREMENAR_MAPINFOMODEL_H_
