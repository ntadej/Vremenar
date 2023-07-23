/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* Based on https://github.com/Countly/countly-sdk-cpp
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <cctype>
#include <iomanip>
#include <sstream>

#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>

#include "common/NetworkManager.h"
#include "common/api/APIRequestBase.h"

#include "Countly.h"

namespace
{
constexpr int COUNTLY_POST_THRESHOLD = 2000;
constexpr int COUNTLY_KEEPALIVE_INTERVAL = 3000;
} // namespace

namespace Vremenar
{

Countly::Countly(NetworkManager *network,
                 QObject *parent)
    : APILoader(network, parent)
{
}

Countly::~Countly()
{
    stop();
}

void Countly::setAlwaysUsePost(bool value)
{
    _alwaysUsePost = value;
}

void Countly::setDeviceID(const QString &value)
{
    if (_sessionParameters.find(QStringLiteral("device_id")) == _sessionParameters.end() || (!_sessionParameters[QStringLiteral("device_id")].isEmpty() && _sessionParameters[QStringLiteral("device_id")] == value)) {
        _sessionParameters[QStringLiteral("device_id")] = value;
        return;
    }

    if (_activeSession) {
        endSession();
        beginSession();
    }
    _sessionParameters[QStringLiteral("device_id")] = value;
}

void Countly::setMaxEvents(size_t value)
{
    _maxEvents = value;
    if (_eventQueue.size() > value) {
        qWarning() << "Countly: New event queue size is smaller than the old one, dropping the oldest events to fit";
        _eventQueue.resize(value);
    }
}

void Countly::setSalt(const QString &value)
{
    _salt = value;
}

void Countly::setMetrics(const QString &os,
                         const QString &os_version,
                         const QString &device,
                         const QString &resolution,
                         const QString &app_version)
{
    QJsonObject metrics;

    if (!os.isEmpty()) {
        metrics[QStringLiteral("_os")] = os;
    }

    if (!os_version.isEmpty()) {
        metrics[QStringLiteral("_os_version")] = os_version;
    }

    if (!device.isEmpty()) {
        metrics[QStringLiteral("_device")] = device;
    }

    if (!resolution.isEmpty()) {
        metrics[QStringLiteral("_resolution")] = resolution;
    }

    // if (!carrier.isEmpty()) {
    //     metrics[QStringLiteral("_carrier")] = carrier;
    // }

    if (!app_version.isEmpty()) {
        metrics[QStringLiteral("_app_version")] = app_version;
    }

    _sessionParameters[QStringLiteral("metrics")] = Countly::encodeURL(QJsonDocument(metrics).toJson(QJsonDocument::Compact));
}

void Countly::start(const QString &app_key,
                    const QString &host)
{
    if (!host.contains(QStringLiteral("http://")) && !host.contains(QStringLiteral("https://"))) {
        _host = "http://" + host;
    } else {
        _host = host;
    }

    _sessionParameters[QStringLiteral("app_key")] = app_key;

    beginSession();
}

void Countly::stop()
{
    if (_activeSession) {
        endSession();
    }
}

void Countly::beginSession()
{
    if (_activeSession) {
        return;
    }

    const std::chrono::system_clock::time_point now = Countly::getTimestamp();
    const auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("sdk_name"), QStringLiteral("qt-native"));
    query.addQueryItem(QStringLiteral("sdk_version"), QStringLiteral("1.0"));
    query.addQueryItem(QStringLiteral("timestamp"), QString::number(timestamp.count()));
    query.addQueryItem(QStringLiteral("begin_session"), QStringLiteral("1"));
    QMapIterator<QString, QString> it(_sessionParameters);
    while (it.hasNext()) {
        it.next();
        query.addQueryItem(it.key(), it.value());
    }

    request(QStringLiteral("/i"), query);

    _lastSent = Countly::getTimestamp();
    _activeSession = true;
}

void Countly::updateSession()
{
    if (!_activeSession) {
        return;
    }

    QJsonArray events;
    const bool no_events = _eventQueue.empty();
    if (!no_events) {
        for (const QJsonObject &event : _eventQueue) {
            events.append(event);
        }
    }

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(getSessionDuration());

    if (no_events) {
        if (duration.count() > COUNTLY_KEEPALIVE_INTERVAL) {
            QUrlQuery query;
            query.addQueryItem(QStringLiteral("app_key"), _sessionParameters[QStringLiteral("app_key")]);
            query.addQueryItem(QStringLiteral("device_id"), _sessionParameters[QStringLiteral("device_id")]);
            query.addQueryItem(QStringLiteral("session_duration"), QString::number(duration.count()));
            request(QStringLiteral("/i"), query);

            _lastSent += duration;
        }

        return;
    }

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("app_key"), _sessionParameters[QStringLiteral("app_key")]);
    query.addQueryItem(QStringLiteral("device_id"), _sessionParameters[QStringLiteral("device_id")]);
    query.addQueryItem(QStringLiteral("session_duration"), QString::number(duration.count()));
    query.addQueryItem(QStringLiteral("events"), QJsonDocument(events).toJson());
    request(QStringLiteral("/i"), query);

    _lastSent = Countly::getTimestamp();
    _eventQueue.clear();
}

void Countly::endSession()
{
    const std::chrono::system_clock::time_point now = Countly::getTimestamp();
    const auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(getSessionDuration(now));

    QUrlQuery query;
    query.addQueryItem(QStringLiteral("app_key"), _sessionParameters[QStringLiteral("app_key")]);
    query.addQueryItem(QStringLiteral("device_id"), _sessionParameters[QStringLiteral("device_id")]);
    query.addQueryItem(QStringLiteral("session_duration"), QString::number(duration.count()));
    query.addQueryItem(QStringLiteral("timestamp"), QString::number(timestamp.count()));
    query.addQueryItem(QStringLiteral("end_session"), QStringLiteral("1"));
    request(QStringLiteral("/i"), query);

    _lastSent = now;
    _activeSession = false;
}

void Countly::addEvent(const Event &event)
{
    if (_eventQueue.size() == _maxEvents) {
        qWarning() << "Countly: Event queue is full, dropping the oldest event to insert a new one";
        _eventQueue.pop_front();
    }
    _eventQueue.push_back(event.json());
}

void Countly::request(const QString &path,
                      QUrlQuery query)
{
    QString data = query.toString(QUrl::FullyEncoded);
    const bool usePost = _alwaysUsePost || (data.size() > COUNTLY_POST_THRESHOLD);

    if (!_salt.isEmpty()) {
        const QString saltedData = data + _salt;
        const QByteArray hashBA = QCryptographicHash::hash(saltedData.toUtf8(), QCryptographicHash::Sha256);
        const QString hash = QLatin1String(hashBA.toHex());

        if (!data.isEmpty()) {
            data += '&';
        }

        data += QStringLiteral("checksum256=");
        data += hash;

        query.addQueryItem(QStringLiteral("checksum256"), hash);
    }

    APIRequestBase request;
    request.setSilent(true);
    request.setBaseUrl(_host);
    request.setCall(QStringLiteral("/countly"));
    if (usePost) {
        request.setOperation(QNetworkAccessManager::PostOperation);
        request.setUrl(path);
        request.setData(data);
    } else {
        request.setUrl(path, query);
    }

    APILoader::request(request);
}

void Countly::response(QNetworkReply *reply)
{
    if (!validResponse(reply)) {
        return;
    }

    // qDebug() << "Countly request done:" << reply->url() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    removeResponse(reply);
}

std::chrono::system_clock::time_point Countly::getTimestamp()
{
    return std::chrono::system_clock::now();
}

std::chrono::system_clock::duration Countly::getSessionDuration(std::chrono::system_clock::time_point now)
{
    const std::chrono::system_clock::duration duration = _lastSent - now;
    return duration;
}

std::chrono::system_clock::duration Countly::getSessionDuration()
{
    return Countly::getSessionDuration(Countly::getTimestamp());
}

QString Countly::encodeURL(const QString &data)
{
    std::ostringstream encoded;

    for (const char character : data.toStdString()) {
        if (std::isalnum(character) != 0 || character == '.' || character == '_' || character == '~') {
            encoded << character;
        } else {
            encoded << '%' << std::setw(2) << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(character));
        }
    }

    return QString::fromStdString(encoded.str());
}

} // namespace Vremenar
