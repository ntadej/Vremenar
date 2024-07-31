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

#include "weather/containers/StationInfo.h"

#include "common/ListItem.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtPositioning/QGeoCoordinate>

#include <memory>
#include <utility>

using Qt::Literals::StringLiterals::operator""_L1;

namespace Vremenar
{

StationInfo::StationInfo(const QString &id,
                         QString name,
                         QGeoCoordinate coordinate,
                         qreal zoomLevel,
                         bool forecastOnly,
                         QString alertsArea,
                         QObject *parent)
    : ListItem(parent),
      _name(std::move(name)),
      _coordinate(std::move(coordinate)),
      _zoomLevel(zoomLevel),
      _forecastOnly(forecastOnly),
      _alertsArea(std::move(alertsArea))
{
    setId(id);
}

std::unique_ptr<StationInfo> StationInfo::fromJson(const QJsonObject &json)
{
    const QString id = json["id"_L1].toString();
    const QString name = json["name"_L1].toString();

    const QJsonObject coordinateObj = json["coordinate"_L1].toObject();
    const QGeoCoordinate coordinate{
        coordinateObj["latitude"_L1].toDouble(),
        coordinateObj["longitude"_L1].toDouble(),
        coordinateObj["altitude"_L1].toDouble()};

    const qreal zoomLevel = json["zoom_level"_L1].toDouble();

    bool forecastOnly{};
    if (json.contains("forecast_only"_L1)) {
        forecastOnly = json["forecast_only"_L1].toBool();
    }
    QString alertsArea;
    if (json.contains("alerts_area"_L1)) {
        alertsArea = json["alerts_area"_L1].toString();
    }

    return std::make_unique<StationInfo>(id, name, coordinate, zoomLevel, forecastOnly, alertsArea);
}

QString StationInfo::display() const
{
    return _name;
}

QString StationInfo::displayCurrent() const
{
    if (forecastOnly()) {
        QString name = _name;
        name.append(" ("_L1).append(currentWeatherSource()->display()).append("_L1");
        return name;
    }

    return _name;
}

QVariant StationInfo::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
    case EditRole:
        return display();
    case CoordinateRole:
        return QVariant::fromValue(coordinate());
    case ZoomLevelRole:
        return zoomLevel();
    case ForecastOnlyRole:
        return forecastOnly();
    case AlertsAreaRole:
        return alertsArea();
    default:
        return {};
    }

    return {};
}

void StationInfo::setCurrentWeatherSource(std::unique_ptr<StationInfo> source)
{
    if (!forecastOnly()) {
        return;
    }

    _currentWeatherSource = std::move(source);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_StationInfo.cpp"
// NOLINTEND
