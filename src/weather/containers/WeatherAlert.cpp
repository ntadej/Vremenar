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

#include "weather/containers/WeatherAlert.h"

#include "common/ListItem.h"
#include "weather/Weather.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include <memory>
#include <utility>

using Qt::Literals::StringLiterals::operator""_L1;

namespace Vremenar
{

WeatherAlert::WeatherAlert(const QString &id,
                           QString event,
                           QString headline,
                           QString description,
                           Weather::AlertType type,
                           Weather::AlertSeverity severity,
                           qint64 onset,
                           qint64 ending,
                           QObject *parent)
    : ListItem(parent),
      _type(type),
      _severity(severity),
      _event(std::move(event)),
      _headline(std::move(headline)),
      _description(std::move(description)),
      _onset(onset),
      _ending(ending)
{
    setId(id);
}

std::unique_ptr<WeatherAlert> WeatherAlert::fromJson(const QJsonObject &json)
{
    const QString id = json["id"_L1].toString();
    const QString event = json["event"_L1].toString();
    const QString headline = json["headline"_L1].toString();
    const QString description = json["description"_L1].toString();
    const Weather::AlertType type = Weather::alertTypeFromString(json["type"_L1].toString());
    const Weather::AlertSeverity severity = Weather::alertSeverityFromString(json["severity"_L1].toString());
    const qint64 onset = json["onset"_L1].toString().toLongLong();
    const qint64 ending = json["ending"_L1].toString().toLongLong();

    return std::make_unique<WeatherAlert>(id, event, headline, description, type, severity, onset, ending);
}

QString WeatherAlert::display() const
{
    return _event;
}

QVariant WeatherAlert::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
    case EventRole:
        return display();
    case TypeRole:
        return type();
    case SeverityRole:
        return severity();
    case HeadlineRole:
        return headline();
    case DescriptionRole:
        return description();
    case DurationRole:
        return duration();
    case OnsetRole:
        return onset();
    case EndingRole:
        return ending();
    default:
        return {};
    }

    return {};
}

QString WeatherAlert::duration() const
{
    auto onset = QDateTime::fromMSecsSinceEpoch(_onset);
    auto ending = QDateTime::fromMSecsSinceEpoch(_ending);

    if (onset.daysTo(ending) != 0) {
        return "%1, %2 – %3, %4"_L1.arg(Weather::dateDisplay(onset), Weather::timeDisplay(onset), Weather::dateDisplay(ending), Weather::timeDisplay(ending));
    }
    return "%1, %2–%3"_L1.arg(Weather::dateDisplay(onset), Weather::timeDisplay(onset), Weather::timeDisplay(ending));
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_WeatherAlert.cpp"
// NOLINTEND
