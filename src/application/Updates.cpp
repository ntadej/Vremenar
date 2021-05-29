/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QVersionNumber>

#include "application/Updates.h"
#include "common/NetworkManager.h"
#include "common/api/APIRequestBase.h"

#include "Config.h"

namespace Vremenar
{

Updates::Updates(NetworkManager *network,
                 QObject *parent)
    : APILoader(network, parent)
{
#ifdef Q_OS_MACOS
    _sparkle = std::make_unique<SparkleHelper>();
#endif
}

void Updates::checkVersion()
{
    request();
}

void Updates::checkForUpdates()
{
#ifdef Q_OS_MACOS
    _sparkle->checkForUpdates();
#else
    request();
#endif
}

void Updates::request()
{
    APIRequestBase request;
    request.setBaseUrl(Vremenar::APIEndpoint);
    request.setCall(QStringLiteral("/version"));
    request.setUrl(QStringLiteral("/version"));
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    currentReplies()->insert(network()->request(request), request);
}

void Updates::response(QNetworkReply *reply)
{
    if (!currentReplies()->contains(reply)) {
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (currentReplies()->value(reply).call() == QStringLiteral("/version")) {
        _server = document[QStringLiteral("server")].toString();
        Q_EMIT serverChanged();

#if !defined(Q_OS_MACOS) && !defined(VREMENAR_STORE)
        QString stable = document[QStringLiteral("stable")].toString();
        QString beta = document[QStringLiteral("beta")].toString();
        compareVersion(stable, beta);
#endif
    }

    removeResponse(reply);
}

void Updates::compareVersion(const QString &stable,
                             const QString &beta)
{
    QVersionNumber currentVersion = QVersionNumber::fromString(Vremenar::version).normalized();
    QVersionNumber stableVersion = QVersionNumber::fromString(stable).normalized();
    QVersionNumber betaVersion = QVersionNumber::fromString(beta).normalized();

    if (!stableVersion.isNull() && currentVersion == stableVersion) {
        qDebug() << "Running current stable version:" << currentVersion;
    } else if (!betaVersion.isNull() && currentVersion == betaVersion) {
        qDebug() << "Running current testing version:" << currentVersion;
    } else {
        if (!stableVersion.isNull() && currentVersion < stableVersion) {
            qDebug() << "Update available:" << stableVersion;
            _message = tr("An update is available. Do you want to download it now?");
            _url = QStringLiteral("https://vremenar.tano.si");
            Q_EMIT messageChanged();
            Q_EMIT updateAvailable();
        } else if (!betaVersion.isNull() && currentVersion < betaVersion) {
            qDebug() << "Testing update available:" << betaVersion;
            _message = tr("A new testing update is available. Do you want to download it now?");
            _url = QStringLiteral("https://vremenar.tano.si");
            Q_EMIT messageChanged();
            Q_EMIT updateAvailable();
        } else {
            qDebug() << "Running development version:" << currentVersion;
        }
    }
}

} // namespace Vremenar
