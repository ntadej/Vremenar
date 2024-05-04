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

#ifndef VREMENAR_NETWORKMANAGER_H_
#define VREMENAR_NETWORKMANAGER_H_

#include "common/api/APIRequestBase.h"

#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <memory>

class QNetworkDiskCache;

namespace Vremenar
{

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    QNetworkReply *request(const APIRequestBase &request);

signals:
    void error(QNetworkReply *,              // NOLINT(readability-named-parameter)
               QNetworkReply::NetworkError); // NOLINT(readability-named-parameter)
    void result(QNetworkReply *);            // NOLINT(readability-named-parameter)

private slots:
    void httpError(QNetworkReply::NetworkError err);
    void httpRequestFinished();

private:
    std::unique_ptr<QNetworkDiskCache> _cache;
};

} // namespace Vremenar

#endif // VREMENAR_NETWORKMANAGER_H_
