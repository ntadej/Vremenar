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

#include <QtCore/QDateTime>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/backend/Common.h"
#include "weather/backend/models/WeatherMapModel.h"

namespace Vremenar
{

Backend::WeatherMapModel::WeatherMapModel(QObject *parent)
    : WeatherMapModelBase(parent) {}

WeatherInfo *Backend::WeatherMapModel::createEntry(const QJsonObject &data)
{
    QString id = data[QStringLiteral("id")].toString();
    QString title = data[QStringLiteral("title")].toString();
    Weather::ObservationType observation = Weather::observationTypeFromString(data[QStringLiteral("observation")].toString());
    QDateTime time = QDateTime::fromMSecsSinceEpoch(data[QStringLiteral("timestamp")].toString().toULongLong());
    QString icon = data[QStringLiteral("icon")].toString();

    double temperature{};
    double temperatureLow{-1000}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    if (data.contains(QStringLiteral("temperature_low")) && !data[QStringLiteral("temperature_low")].isNull()) {
        temperature = data[QStringLiteral("temperature")].toDouble();
        temperatureLow = data[QStringLiteral("temperature_low")].toDouble();
    } else {
        temperature = data[QStringLiteral("temperature")].toDouble();
    }

    QJsonObject coordinateObj = data[QStringLiteral("coordinate")].toObject();
    QGeoCoordinate coordinate{coordinateObj[QStringLiteral("latitude")].toDouble(), coordinateObj[QStringLiteral("longitude")].toDouble()};

    qreal zoomLevel = data[QStringLiteral("zoom_level")].toDouble();

    return appendRow(std::make_unique<WeatherInfo>(id, observation, time.toMSecsSinceEpoch(), title, icon, temperature, temperatureLow, coordinate, zoomLevel));
}

void Backend::WeatherMapModel::addEntries(const QJsonArray &data)
{
    for (const QJsonValue &obj : data) {
        createEntry(obj.toObject());
    }
}

} // namespace Vremenar
