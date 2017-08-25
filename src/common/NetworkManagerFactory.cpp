/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/NetworkManager.h"
#include "common/NetworkManagerFactory.h"

NetworkManagerFactory::NetworkManagerFactory(QObject *parent)
    : QObject(parent) {}

NetworkManagerFactory::~NetworkManagerFactory() {}

QNetworkAccessManager *NetworkManagerFactory::create(QObject *parent)
{
    _nam = new NetworkManager(parent);
    return _nam;
}