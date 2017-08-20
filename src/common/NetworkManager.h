/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_NETWORKMANAGER_H_
#define VREMENAR_NETWORKMANAGER_H_

#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QtNetwork/QNetworkReply>

#include "weather/common/api/APIRequest.h"

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    QNetworkReply *request(APIRequest &request);

signals:
    void error(QNetworkReply *,
               QNetworkReply::NetworkError);
    void result(QNetworkReply *);

private slots:
    void httpError(QNetworkReply::NetworkError err);
    void httpRequestFinished();

private:
    QNetworkDiskCache *_cache;
};

#endif // VREMENAR_NETWORKMANAGER_H_
