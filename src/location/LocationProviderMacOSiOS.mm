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

#include "location/LocationProviderMacOSiOS.h"
#include "location/LocationProvider.h"

@implementation LocationProviderDelegate {
    Vremenar::LocationProvider *_locationProvider;
}

- (instancetype)initWith:(Vremenar::LocationProvider *)locationProvider
{
    if ((self = [self init]) != nullptr) {
        _locationProvider = locationProvider;
    }
    return self;
}
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{
    Q_UNUSED(manager)
    Q_UNUSED(status)

    _locationProvider->supportedMethodsChanged();
}

@end

namespace Vremenar
{

LocationProviderMacOSiOS::LocationProviderMacOSiOS(LocationProvider *provider)
{
    _delegate = [[LocationProviderDelegate alloc] initWith:provider];

    _locationManager = [[CLLocationManager alloc] init];
    _locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    _locationManager.delegate = _delegate;
}

LocationProviderMacOSiOS::~LocationProviderMacOSiOS()
{
    [_locationManager release];
    [_delegate release];
}

bool LocationProviderMacOSiOS::servicesEnabled() const
{
    return [CLLocationManager locationServicesEnabled] != 0;
}

bool LocationProviderMacOSiOS::servicesAllowed() const
{
    if (!servicesEnabled()) {
        return false;
    }

    switch ([CLLocationManager authorizationStatus]) {
    case kCLAuthorizationStatusNotDetermined:
        // User has not yet made a choice with regards to this application
        break;
    case kCLAuthorizationStatusRestricted:
        // This application is not authorized to use location services.  Due
        // to active restrictions on location services, the user cannot change
        // this status, and may not have personally denied authorization
        return false;
    case kCLAuthorizationStatusDenied:
        // User has explicitly denied authorization for this application, or
        // location services are disabled in Settings
        return false;
    case kCLAuthorizationStatusAuthorizedAlways:
        // This app is authorized to start location services at any time.
        break;
#ifndef Q_OS_MACOS
    case kCLAuthorizationStatusAuthorizedWhenInUse:
        // This app is authorized to start most location services while running in the foreground.
        break;
#endif
    default:
        // By default, try to enable it
        break;
    }

    return true;
}

void LocationProvider::initMacOSiOS()
{
    _platform = std::make_unique<LocationProviderMacOSiOS>(this);
}

} // namespace Vremenar
