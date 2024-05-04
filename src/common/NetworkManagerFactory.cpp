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

#include "common/NetworkManagerFactory.h"

#include "common/NetworkManager.h"

#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>

namespace Vremenar
{

NetworkManagerFactory::NetworkManagerFactory(QObject *parent)
    : QObject(parent) {}

QNetworkAccessManager *NetworkManagerFactory::create(QObject *parent)
{
    return new NetworkManager(parent); // NOLINT(cppcoreguidelines-owning-memory)
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_NetworkManagerFactory.cpp"
// NOLINTEND
