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

#ifndef VREMENAR_APILOADER_H_
#define VREMENAR_APILOADER_H_

#include "common/api/APIRequestBase.h"

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

namespace Vremenar
{

class NetworkManager;

class APILoader : public QObject
{
    Q_OBJECT
public:
    explicit APILoader(NetworkManager *network,
                       QObject *parent = nullptr);

    Q_PROPERTY(bool requesting READ requesting NOTIFY requestingChanged)

    void request(const APIRequestBase &request);
    [[nodiscard]] bool validResponse(QNetworkReply *reply);
    [[nodiscard]] APIRequestBase requestFromResponse(QNetworkReply *reply);
    void removeResponse(QNetworkReply *reply);

signals:
    void requestingChanged();

protected slots:
    virtual void error(QNetworkReply *reply,
                       QNetworkReply::NetworkError err);
    virtual void response(QNetworkReply *reply);

protected:
    NetworkManager *network() { return _network; }

private:
    [[nodiscard]] bool requesting() const { return _requesting; }

    NetworkManager *_network; // not owned
    bool _requesting{false};

    QMap<QNetworkReply *, APIRequestBase> _currentReplies;
};

} // namespace Vremenar

#endif // VREMENAR_APILOADER_H_
