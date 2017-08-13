/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LOCATIONPROVIDER_H_
#define VREMENAR_LOCATIONPROVIDER_H_

#include <QtCore/QObject>
#include <QtLocation/QGeoServiceProvider>

class LocationProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString providerAppId READ providerAppId CONSTANT)
    Q_PROPERTY(QString providerAppToken READ providerAppToken CONSTANT)
public:
    explicit LocationProvider(QObject *parent = nullptr);
    virtual ~LocationProvider();

    static QString providerAppId();
    static QString providerAppToken();

private:
    QGeoServiceProvider *_provider;
};

#endif // VREMENAR_LOCATIONPROVIDER_H_
