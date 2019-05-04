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

#ifndef VREMENAR_NETWORKMANAGERFACTORY_H_
#define VREMENAR_NETWORKMANAGERFACTORY_H_

#include <QtNetwork/QNetworkAccessManager>
#include <QtQml/QQmlNetworkAccessManagerFactory>

namespace Vremenar
{

class NetworkManagerFactory : public QObject, public QQmlNetworkAccessManagerFactory
{
    Q_OBJECT
public:
    NetworkManagerFactory(QObject *parent = nullptr);
    ~NetworkManagerFactory() = default;

    virtual QNetworkAccessManager *create(QObject *parent);
};

} // namespace Vremenar

#endif // VREMENAR_NETWORKMANAGERFACTORY_H_
