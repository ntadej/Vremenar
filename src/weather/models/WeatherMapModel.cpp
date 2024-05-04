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

#include "weather/models/WeatherMapModel.h"

#include "common/ListModel.h"
#include "weather/containers/StationInfo.h"
#include "weather/containers/WeatherCondition.h"
#include "weather/containers/WeatherInfo.h"
#include "weather/models/StationListModel.h"

#include <QtCore/QJsonArray>
#include <QtCore/QObject>
#include <QtCore/QStringLiteral>

#include <memory>

namespace Vremenar
{

WeatherMapModel::WeatherMapModel(QObject *parent)
    : ListModel(WeatherInfo::roleNames(), parent) {}

void WeatherMapModel::addEntries(StationListModel *stations,
                                 const QJsonArray &data)
{
    for (const auto &obj : data) {
        const QJsonObject object = obj.toObject();
        const StationInfo *station = stations->find<StationInfo>(object[QStringLiteral("station")].toObject()[QStringLiteral("id")].toString());
        appendRow(std::make_unique<WeatherInfo>(
            std::make_unique<StationInfo>(station->id(), station->display(), station->coordinate(), station->zoomLevel(), station->forecastOnly(), station->alertsArea()),
            WeatherCondition::fromJson(object[QStringLiteral("condition")].toObject())));
    }
}

void WeatherMapModel::update(WeatherMapModel *model,
                             qint64 time)
{
    for (int i = 0; i < model->rowCount(); i++) {
        const auto *entry = model->row<WeatherInfo>(i);
        if (entry->condition()->time() != time) {
            continue;
        }

        auto *toUpdate = find<WeatherInfo>(entry->id());
        if (toUpdate == nullptr) {
            continue;
        }

        toUpdate->update(entry);
    }

    emit dataChanged(index(0), index(rowCount() - 1));
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_WeatherMapModel.cpp"
// NOLINTEND
