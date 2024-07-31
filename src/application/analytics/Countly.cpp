/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* Based on https://github.com/Countly/countly-sdk-cpp
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "Countly.h"

#include "common/NetworkManager.h"
#include "common/api/APILoader.h"
#include "common/api/APIRequestBase.h"

#include <QtCore/QCryptographicHash>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QLatin1StringView>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <cctype>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <sstream>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

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
    if (_sessionParameters.find(u"device_id"_s) == _sessionParameters.end() || (!_sessionParameters[u"device_id"_s].isEmpty() && _sessionParameters[u"device_id"_s] == value)) {
        _sessionParameters[u"device_id"_s] = value;
        return;
    }

    if (_activeSession) {
        endSession();
        beginSession();
    }
    _sessionParameters[u"device_id"_s] = value;
}

void Countly::setMaxEvents(std::size_t value)
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
        metrics["_os"_L1] = os;
    }

    if (!os_version.isEmpty()) {
        metrics["_os_version"_L1] = os_version;
    }

    if (!device.isEmpty()) {
        metrics["_device"_L1] = device;
    }

    if (!resolution.isEmpty()) {
        metrics["_resolution"_L1] = resolution;
    }

    // if (!carrier.isEmpty()) {
    //     metrics["_carrier"_L1] = carrier;
    // }

    if (!app_version.isEmpty()) {
        metrics["_app_version"_L1] = app_version;
    }

    _sessionParameters[u"metrics"_s] = Countly::encodeURL(QJsonDocument(metrics).toJson(QJsonDocument::Compact));
}

void Countly::start(const QString &app_key,
                    const QString &host)
{
    if (!host.contains("http://"_L1) && !host.contains("https://"_L1)) {
        _host = "http://" + host;
    } else {
        _host = host;
    }

    _sessionParameters[u"app_key"_s] = app_key;

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
    query.addQueryItem(u"sdk_name"_s, u"qt-native"_s);
    query.addQueryItem(u"sdk_version"_s, u"1.0"_s);
    query.addQueryItem(u"timestamp"_s, QString::number(timestamp.count()));
    query.addQueryItem(u"begin_session"_s, u"1"_s);
    QMapIterator<QString, QString> it(_sessionParameters);
    while (it.hasNext()) {
        it.next();
        query.addQueryItem(it.key(), it.value());
    }

    request(u"/i"_s, query);

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
            query.addQueryItem(u"app_key"_s, _sessionParameters[u"app_key"_s]);
            query.addQueryItem(u"device_id"_s, _sessionParameters[u"device_id"_s]);
            query.addQueryItem(u"session_duration"_s, QString::number(duration.count()));
            request(u"/i"_s, query);

            _lastSent += duration;
        }

        return;
    }

    QUrlQuery query;
    query.addQueryItem(u"app_key"_s, _sessionParameters[u"app_key"_s]);
    query.addQueryItem(u"device_id"_s, _sessionParameters[u"device_id"_s]);
    query.addQueryItem(u"session_duration"_s, QString::number(duration.count()));
    query.addQueryItem(u"events"_s, QJsonDocument(events).toJson());
    request(u"/i"_s, query);

    _lastSent = Countly::getTimestamp();
    _eventQueue.clear();
}

void Countly::endSession()
{
    const std::chrono::system_clock::time_point now = Countly::getTimestamp();
    const auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    const auto duration = std::chrono::duration_cast<std::chrono::seconds>(getSessionDuration(now));

    QUrlQuery query;
    query.addQueryItem(u"app_key"_s, _sessionParameters[u"app_key"_s]);
    query.addQueryItem(u"device_id"_s, _sessionParameters[u"device_id"_s]);
    query.addQueryItem(u"session_duration"_s, QString::number(duration.count()));
    query.addQueryItem(u"timestamp"_s, QString::number(timestamp.count()));
    query.addQueryItem(u"end_session"_s, u"1"_s);
    request(u"/i"_s, query);

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
        const auto hash = QString::fromLatin1(hashBA.toHex());

        if (!data.isEmpty()) {
            data += '&';
        }

        data += "checksum256="_L1;
        data += hash;

        query.addQueryItem(u"checksum256"_s, hash);
    }

    APIRequestBase request;
    request.setSilent(true);
    request.setBaseUrl(_host);
    request.setCall(u"/countly"_s);
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
