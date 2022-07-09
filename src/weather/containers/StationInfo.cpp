/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/containers/StationInfo.h"

namespace Vremenar
{

StationInfo::StationInfo(const QString &id,
                         QString name,
                         const QGeoCoordinate &coordinate,
                         qreal zoomLevel,
                         bool forecastOnly,
                         QString alertsArea,
                         QObject *parent)
    : ListItem(parent),
      _name(std::move(name)),
      _coordinate(coordinate),
      _zoomLevel(zoomLevel),
      _forecastOnly(forecastOnly),
      _alertsArea(std::move(alertsArea))
{
    setId(id);
}

std::unique_ptr<StationInfo> StationInfo::fromJson(const QJsonObject &json)
{
    QString id = json[QStringLiteral("id")].toString();
    QString name = json[QStringLiteral("name")].toString();

    QJsonObject coordinateObj = json[QStringLiteral("coordinate")].toObject();
    QGeoCoordinate coordinate{
        coordinateObj[QStringLiteral("latitude")].toDouble(),
        coordinateObj[QStringLiteral("longitude")].toDouble(),
        coordinateObj[QStringLiteral("altitude")].toDouble()};

    qreal zoomLevel = json[QStringLiteral("zoom_level")].toDouble();

    bool forecastOnly{};
    if (json.contains(QStringLiteral("forecast_only"))) {
        forecastOnly = json[QStringLiteral("forecast_only")].toBool();
    }
    QString alertsArea;
    if (json.contains(QStringLiteral("alerts_area"))) {
        alertsArea = json[QStringLiteral("alerts_area")].toString();
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
        name.append(QStringLiteral(" (")).append(currentWeatherSource()->display()).append(QStringLiteral(")"));
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

#include "moc_StationInfo.cpp"
