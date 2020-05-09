/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_LOCATIONPROVIDERMACOSIOS_H_
#define VREMENAR_LOCATIONPROVIDERMACOSIOS_H_

#import <CoreLocation/CoreLocation.h>

#include "location/LocationProviderPlatform.h"

@interface LocationProviderDelegate : NSObject <CLLocationManagerDelegate>
@end

namespace Vremenar
{

class LocationProvider;

class LocationProviderMacOSiOS final : public LocationProviderPlatform
{
public:
    explicit LocationProviderMacOSiOS(LocationProvider *provider);
    ~LocationProviderMacOSiOS() override;

    bool servicesEnabled() const final;
    bool servicesAllowed() const final;

private:
    CLLocationManager *_locationManager;
    LocationProviderDelegate *_delegate;
};

} // namespace Vremenar

#endif // VREMENAR_LOCATIONPROVIDERMACOSIOS_H_
