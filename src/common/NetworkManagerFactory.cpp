/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/NetworkManager.h"

#include "common/NetworkManagerFactory.h"

namespace Vremenar
{

NetworkManagerFactory::NetworkManagerFactory(QObject *parent)
    : QObject(parent) {}

QNetworkAccessManager *NetworkManagerFactory::create(QObject *parent)
{
    return new NetworkManager(parent);
}

} // namespace Vremenar
