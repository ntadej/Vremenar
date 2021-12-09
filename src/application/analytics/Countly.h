/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
* 
* Based on https://github.com/Countly/countly-sdk-cpp
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef COUNTLY_H_
#define COUNTLY_H_

#include <chrono>
#include <deque>

#include <QtCore/QJsonObject>

#include "common/api/APILoader.h"

namespace Vremenar
{

class Countly final : public APILoader
{
    Q_OBJECT
public:
    explicit Countly(NetworkManager *network,
                     QObject *parent = nullptr);
    Countly(const Countly &reader) = delete;
    Countly &operator=(const Countly &q) = delete;
    ~Countly() final;

    void setAlwaysUsePost(bool value);
    void setDeviceID(const QString &value);
    void setMaxEvents(size_t value);
    void setSalt(const QString &value);

    void setMetrics(const QString &os,
                    const QString &os_version,
                    const QString &device,
                    const QString &resolution,
                    const QString &app_version);

    void start(const QString &app_key,
               const QString &host);
    void stop();

    void beginSession();
    void updateSession();
    void endSession();

    class Event
    {
    public:
        explicit Event(const QString &key,
                       int count = 1);
        explicit Event(const QString &key,
                       int count,
                       double sum);

        [[nodiscard]] QJsonObject json() const { return _object; }

    private:
        QJsonObject _object;
    };

    void addEvent(const Event &event);

    void recordEvent(const QString &key,
                     int count)
    {
        addEvent(Event(key, count));
    }

    void recordEvent(const QString &key,
                     int count,
                     double sum)
    {
        addEvent(Event(key, count, sum));
    }

private:
    void request(const QString &path,
                 QUrlQuery query);
    void response(QNetworkReply *reply) final;

    static std::chrono::system_clock::time_point getTimestamp();
    std::chrono::system_clock::duration getSessionDuration(std::chrono::system_clock::time_point now);
    std::chrono::system_clock::duration getSessionDuration();

    QString encodeURL(const QString &data);

    QString _host;
    bool _alwaysUsePost{};
    std::chrono::system_clock::time_point _lastSent{};
    bool _activeSession{};

    QMap<QString, QString> _sessionParameters;
    QString _salt;

    size_t _maxEvents{200}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    std::deque<QJsonObject> _eventQueue;
};

} // namespace Vremenar

#endif // COUNTLY_H_
