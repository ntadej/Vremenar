/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_NETWORKMANAGER_H_
#define VREMENAR_NETWORKMANAGER_H_

#include <memory>

#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkReply>

#include "common/api/APIRequestBase.h"

namespace Vremenar
{

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    QNetworkReply *request(const APIRequestBase &request);

signals:
    void error(QNetworkReply *,
               QNetworkReply::NetworkError);
    void result(QNetworkReply *);

private slots:
    void httpError(QNetworkReply::NetworkError err);
    void httpRequestFinished();

private:
    std::unique_ptr<QNetworkDiskCache> _cache;
};

} // namespace Vremenar

#endif // VREMENAR_NETWORKMANAGER_H_
