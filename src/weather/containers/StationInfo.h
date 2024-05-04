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

#ifndef VREMENAR_STATIONINFO_H_
#define VREMENAR_STATIONINFO_H_

#include "common/ListItem.h"

#include <QtCore/QHash>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtPositioning/QGeoCoordinate>

#include <cstdint>
#include <memory>

namespace Vremenar
{

class StationInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QString displayCurrent READ displayCurrent CONSTANT)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate CONSTANT)
    Q_PROPERTY(qreal zoomLevel READ zoomLevel CONSTANT)
public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        EditRole = Qt::EditRole,
        IdRole = Qt::UserRole + 1,
        CoordinateRole,
        ZoomLevelRole,
        ForecastOnlyRole,
        AlertsAreaRole,
    };

    explicit StationInfo(const QString &id,
                         QString name,
                         QGeoCoordinate coordinate,
                         qreal zoomLevel,
                         bool forecastOnly,
                         QString alertsArea,
                         QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;
    [[nodiscard]] QString displayCurrent() const;

    [[nodiscard]] static std::unique_ptr<StationInfo> fromJson(const QJsonObject &json);

    [[nodiscard]] const QGeoCoordinate &coordinate() const { return _coordinate; }
    [[nodiscard]] qreal zoomLevel() const { return _zoomLevel; }
    [[nodiscard]] bool forecastOnly() const { return _forecastOnly; }
    [[nodiscard]] const QString &alertsArea() const { return _alertsArea; }
    [[nodiscard]] const StationInfo *currentWeatherSource() const { return _currentWeatherSource.get(); }
    void setCurrentWeatherSource(std::unique_ptr<StationInfo> source);

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {EditRole, "edit"},
            {CoordinateRole, "coordinate"},
            {ZoomLevelRole, "zoomLevel"},
            {ForecastOnlyRole, "forecastOnly"},
            {AlertsAreaRole, "alertsArea"}};
    }

private:
    QString _name;
    QGeoCoordinate _coordinate;
    qreal _zoomLevel{};
    bool _forecastOnly{};
    QString _alertsArea;
    std::unique_ptr<StationInfo> _currentWeatherSource;
};

} // namespace Vremenar

// NOLINTNEXTLINE
Q_DECLARE_METATYPE(Vremenar::StationInfo *)

#endif // VREMENAR_STATIONINFO_H_
