/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOWEATHERPROVIDER_H_
#define VREMENAR_ARSOWEATHERPROVIDER_H_

#include "weather/common/WeatherProvider.h"

class ARSOMapLayersModel;

class ARSOWeatherProvider : public WeatherProvider
{
    Q_OBJECT
public:
    explicit ARSOWeatherProvider(NetworkManager *network = nullptr,
                                 QObject *parent = nullptr);
    ~ARSOWeatherProvider();

    Q_INVOKABLE void requestMapLayers(Vremenar::Weather::MapType type) override;

protected slots:
    void response(QNetworkReply *reply) override;

private:
    ARSOMapLayersModel *_mapLayersModel;
};

#endif // VREMENAR_ARSOWEATHERPROVIDER_H_
