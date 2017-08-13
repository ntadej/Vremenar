/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_NETWORKMANAGERFACTORY_H_
#define VREMENAR_NETWORKMANAGERFACTORY_H_

#include <QtNetwork/QNetworkAccessManager>
#include <QtQml/QQmlNetworkAccessManagerFactory>

class NetworkManager;

class NetworkManagerFactory : public QObject, public QQmlNetworkAccessManagerFactory
{
    Q_OBJECT
public:
    NetworkManagerFactory(QObject *parent = 0);
    ~NetworkManagerFactory();

    virtual QNetworkAccessManager *create(QObject *parent);

private:
    NetworkManager *_nam;
};

#endif // VREMENAR_NETWORKMANAGERFACTORY_H_
