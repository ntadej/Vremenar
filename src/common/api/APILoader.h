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

#ifndef VREMENAR_APILOADER_H_
#define VREMENAR_APILOADER_H_

#include <QtCore/QThread>
#include <QtNetwork/QNetworkReply>

#include "common/api/APIRequestBase.h"

namespace Vremenar
{

class NetworkManager;

class APILoader : public QObject
{
    Q_OBJECT
public:
    explicit APILoader(NetworkManager *network,
                       QObject *parent = nullptr);

    void removeResponse(QNetworkReply *reply);

protected Q_SLOTS:
    virtual void error(QNetworkReply *reply,
                       QNetworkReply::NetworkError err);
    virtual void response(QNetworkReply *reply);

protected:
    NetworkManager *network() { return _network; }
    QMap<QNetworkReply *, APIRequestBase> *currentReplies() { return &_currentReplies; }

private:
    NetworkManager *_network; // not owned

    QMap<QNetworkReply *, APIRequestBase> _currentReplies;
};

} // namespace Vremenar

#endif // VREMENAR_APILOADER_H_
