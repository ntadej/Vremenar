/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "location/LocationProvider.h"

LocationProvider::LocationProvider(QObject *parent)
    : QObject(parent)
{
    QMap<QString, QVariant> params;
    params["here.app_id"] = providerAppId();
    params["here.token"] = providerAppToken();

    _provider = new QGeoServiceProvider("here", params);
}

LocationProvider::~LocationProvider() {}

QString LocationProvider::providerAppId()
{
#ifdef HERE_APP_ID
    return QString(HERE_APP_ID);
#else
    return QString();
#endif
}

QString LocationProvider::providerAppToken()
{
#ifdef HERE_APP_TOKEN
    return QString(HERE_APP_TOKEN);
#else
    return QString();
#endif
}
