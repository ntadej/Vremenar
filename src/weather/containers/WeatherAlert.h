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

#ifndef VREMENAR_WEATHERALERT_H_
#define VREMENAR_WEATHERALERT_H_

#include <memory>

#include <QtCore/QJsonObject>

#include "common/ListItem.h"
#include "weather/Weather.h"

namespace Vremenar
{

class WeatherAlert : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QString headline READ headline CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(Weather::AlertType type READ type CONSTANT)
    Q_PROPERTY(Weather::AlertSeverity severity READ severity CONSTANT)
    Q_PROPERTY(QString duration READ duration CONSTANT)
    Q_PROPERTY(qint64 onset READ onset CONSTANT)
    Q_PROPERTY(qint64 ending READ ending CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        TypeRole,
        SeverityRole,
        EventRole,
        HeadlineRole,
        DescriptionRole,
        DurationRole,
        OnsetRole,
        EndingRole,
    };

    explicit WeatherAlert(const QString &id,
                          QString event,
                          QString headline,
                          QString description,
                          Weather::AlertType type,
                          Weather::AlertSeverity severity,
                          qint64 onset,
                          qint64 ending,
                          QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] static std::unique_ptr<WeatherAlert> fromJson(const QJsonObject &json);

    [[nodiscard]] inline Weather::AlertType type() const { return _type; }
    [[nodiscard]] inline Weather::AlertSeverity severity() const { return _severity; }
    [[nodiscard]] inline const QString &headline() const { return _headline; }
    [[nodiscard]] inline const QString &description() const { return _description; }
    [[nodiscard]] QString duration() const;
    [[nodiscard]] inline qint64 onset() const { return _onset; }
    [[nodiscard]] inline qint64 ending() const { return _ending; }

    static inline QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {TypeRole, "type"},
            {SeverityRole, "severity"},
            {EventRole, "event"},
            {HeadlineRole, "headline"},
            {DescriptionRole, "description"},
            {DurationRole, "duration"},
            {OnsetRole, "onset"},
            {EndingRole, "ending"}};
    }

private:
    Weather::AlertType _type;
    Weather::AlertSeverity _severity;
    QString _event;
    QString _headline;
    QString _description;
    qint64 _onset;
    qint64 _ending;
};

} // namespace Vremenar

// NOLINTNEXTLINE
Q_DECLARE_METATYPE(Vremenar::WeatherAlert *)

#endif // VREMENAR_WEATHERALERT_H_
