/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_APILOADER_H_
#define VREMENAR_APILOADER_H_

#include <QtCore/QThread>
#include <QtNetwork/QNetworkReply>

#include "weather/common/api/APIRequest.h"

class NetworkManager;

class APILoader : public QObject
{
    Q_OBJECT
public:
    explicit APILoader(NetworkManager *network = nullptr,
                       QObject *parent = nullptr);
    virtual ~APILoader();

    void removeResponse(QNetworkReply *reply);

protected slots:
    virtual void error(QNetworkReply *reply,
                       QNetworkReply::NetworkError err);
    virtual void response(QNetworkReply *reply);

protected:
    NetworkManager *_network;

    QMap<QNetworkReply *, APIRequest> _currentReplies;
};

#endif // VREMENAR_APILOADER_H_