/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/containers/StationInfo.h"
#include "weather/models/StationListModel.h"

namespace Vremenar
{

StationListModel::StationListModel(QObject *parent)
    : ListModel(StationInfo::roleNames(), parent) {}

void StationListModel::addEmpty()
{
    appendRow(std::make_unique<StationInfo>("", tr("None"), QGeoCoordinate(0, 0), 0, false, ""));
}

void StationListModel::addStations(const QJsonArray &data)
{
    for (const auto &stationRef : data) {
        const QJsonObject station = stationRef.toObject();
        appendRow(StationInfo::fromJson(station));
    }
}

void StationListModel::addStationsWithCurrentCondition(StationListModel *model)
{
    for (int i{}; i < model->rowCount(); i++) {
        const StationInfo *station = model->row<StationInfo>(i);
        if (!station->forecastOnly()) {
            appendRow(std::make_unique<StationInfo>(
                station->id(),
                station->display(),
                station->coordinate(),
                station->zoomLevel(),
                station->forecastOnly(),
                station->alertsArea(),
                station->parent()));
        }
    }
}

} // namespace Vremenar

#include "moc_StationListModel.cpp"
