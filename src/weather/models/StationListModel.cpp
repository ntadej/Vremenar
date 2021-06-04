/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/containers/StationListItem.h"
#include "weather/models/StationListModel.h"

namespace Vremenar
{

StationListModel::StationListModel(QObject *parent)
    : ListModel(StationListItem::roleNames(), parent) {}

void StationListModel::addStations(const QJsonArray &data)
{
    for (const QJsonValue &stationRef : data) {
        QJsonObject station = stationRef.toObject();
        appendRow(StationListItem::fromJson(station));
    }
}

} // namespace Vremenar
