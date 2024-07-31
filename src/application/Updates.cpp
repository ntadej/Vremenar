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

#include "application/Updates.h"

#include "common/NetworkManager.h"
#include "common/api/APILoader.h"
#include "common/api/APIRequestBase.h"

#if !defined(VREMENAR_STORE) && (defined(Q_OS_MACOS) || defined(Q_OS_WINDOWS))
#include "application/SparkleHelper.h"
#include <memory>
#endif

#include "Config.h"

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QLatin1StringView>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVersionNumber>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

Updates::Updates(NetworkManager *network,
                 QObject *parent)
    : APILoader(network, parent)
{
#if !defined(VREMENAR_STORE) && (defined(Q_OS_MACOS) || defined(Q_OS_WINDOWS))
    _sparkle = std::make_unique<SparkleHelper>();
#endif
}

Updates::~Updates() = default;

void Updates::checkVersion()
{
    request();
}

void Updates::checkForUpdates()
{
#if defined(VREMENAR_STORE)
    // pass
#elif defined(Q_OS_MACOS) || defined(Q_OS_WINDOWS)
    _sparkle->checkForUpdates();
#else
    request();
#endif
}

void Updates::request()
{
    APIRequestBase request;
    request.setBaseUrl(Vremenar::APIEndpoint);
    request.setCall(u"/version"_s);
    request.setUrl(u"/version"_s);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

    APILoader::request(request);
}

void Updates::response(QNetworkReply *reply)
{
    if (!validResponse(reply)) {
        return;
    }

    const QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (requestFromResponse(reply).call() == "/version"_L1) {
        _server = document["server"_L1].toString();
        emit serverChanged();

#if !defined(VREMENAR_STORE) && !defined(Q_OS_MACOS) && !defined(Q_OS_WINDOWS)
        const QString stable = document["stable"_L1].toString();
        const QString beta = document["beta"_L1].toString();
        compareVersion(stable, beta);
#endif
    }

    removeResponse(reply);
}

void Updates::compareVersion(const QString &stable,
                             const QString &beta)
{
    const QVersionNumber currentVersion = QVersionNumber::fromString(Vremenar::version).normalized();
    const QVersionNumber stableVersion = QVersionNumber::fromString(stable).normalized();
    const QVersionNumber betaVersion = QVersionNumber::fromString(beta).normalized();

    if (!stableVersion.isNull() && currentVersion == stableVersion) {
        qDebug() << "Running current stable version:" << currentVersion;
    } else if (!betaVersion.isNull() && currentVersion == betaVersion) {
        qDebug() << "Running current testing version:" << currentVersion;
    } else {
        if (!stableVersion.isNull() && currentVersion < stableVersion) {
            qDebug() << "Update available:" << stableVersion;
            _message = tr("An update is available. Do you want to download it now?");
            _url = u"https://vremenar.app"_s;
            emit messageChanged();
            emit updateAvailable();
        } else if (!betaVersion.isNull() && currentVersion < betaVersion) {
            qDebug() << "Testing update available:" << betaVersion;
            _message = tr("A new testing update is available. Do you want to download it now?");
            _url = u"https://vremenar.app"_s;
            emit messageChanged();
            emit updateAvailable();
        } else {
            qDebug() << "Running development version:" << currentVersion;
        }
    }
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_Updates.cpp"
// NOLINTEND
