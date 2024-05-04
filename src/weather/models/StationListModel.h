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

#ifndef VREMENAR_STATIONLISTMODEL_H_
#define VREMENAR_STATIONLISTMODEL_H_

#include "common/ListModel.h"

#include <QtCore/QJsonArray>
#include <QtCore/QObject>

namespace Vremenar
{

class StationListModel : public ListModel
{
    Q_OBJECT
public:
    explicit StationListModel(QObject *parent = nullptr);

    void addEmpty();
    void addStations(const QJsonArray &data);
    void addStationsWithCurrentCondition(StationListModel *model);
};

} // namespace Vremenar

#endif // VREMENAR_STATIONLISTMODEL_H_
