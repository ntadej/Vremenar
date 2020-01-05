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

#ifndef VREMENAR_CURRENTWEATHERBASE_H_
#define VREMENAR_CURRENTWEATHERBASE_H_

#include <QtCore/QDateTime>
#include <QtCore/QObject>

namespace Vremenar
{

class CurrentWeatherBase : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWeatherBase(QObject *parent = nullptr);
    virtual ~CurrentWeatherBase() = default;

    Q_PROPERTY(QString location READ location NOTIFY weatherChanged)
    Q_PROPERTY(QString temperature READ temperature NOTIFY weatherChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY weatherChanged)
    Q_PROPERTY(QDateTime time READ time NOTIFY weatherChanged)

    virtual void updateCurrentWeather(const QJsonObject &data) = 0;

    [[nodiscard]] inline const QString &location() const { return _location; }
    [[nodiscard]] QString temperature() const;
    [[nodiscard]] QString temperatureShort() const;
    [[nodiscard]] inline const QString &icon() const { return _icon; }
    [[nodiscard]] inline const QDateTime &time() const { return _time; }

Q_SIGNALS:
    void weatherChanged();

protected:
    void setCurrentWeather(const QString &location,
                           double temperature,
                           const QString &icon,
                           const QDateTime &time);

private:
    QString _location;
    double _temperature{};
    QString _icon;
    QDateTime _time;
};

} // namespace Vremenar

#endif // VREMENAR_CURRENTWEATHERBASE_H_
