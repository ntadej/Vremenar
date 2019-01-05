/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOWEATHERPROVIDER_H_
#define VREMENAR_ARSOWEATHERPROVIDER_H_

#include "weather/common/WeatherProviderBase.h"

namespace Vremenar
{
namespace ARSO
{
class MapLayersModel;

class WeatherProvider : public WeatherProviderBase
{
    Q_OBJECT
public:
    explicit WeatherProvider(NetworkManager *network,
                             QObject *parent = nullptr);
    virtual ~WeatherProvider() final;

    Q_INVOKABLE virtual void requestMapLayers(Weather::MapType type) final;

protected slots:
    virtual void response(QNetworkReply *reply) final;

private:
    std::unique_ptr<MapLayersModel> _mapLayersModel;
};

} // namespace ARSO
} // namespace Vremenar

#endif // VREMENAR_ARSOWEATHERPROVIDER_H_
