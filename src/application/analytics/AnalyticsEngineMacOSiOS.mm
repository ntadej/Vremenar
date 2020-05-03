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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"
#include <Countly/Countly.h>
#pragma clang diagnostic pop

#include "application/analytics/AnalyticsEngineMacOSiOS.h"

#include "Config.h"

namespace Vremenar
{

AnalyticsEngineMacOSiOS::AnalyticsEngineMacOSiOS()
{
    CountlyConfig *config = [[CountlyConfig alloc] init];
    config.appKey = [NSString stringWithUTF8String:Vremenar::CountlyAppKey.data()];
    config.host = [NSString stringWithUTF8String:Vremenar::CountlyEndpoint.data()];
    config.secretSalt = [NSString stringWithUTF8String:Vremenar::CountlySalt.data()];
    config.features = @[ CLYCrashReporting ];
#ifdef QT_DEBUG
    config.enableDebug = YES;
#endif
    [Countly.sharedInstance startWithConfig:config];

    [config release];
}

void AnalyticsEngineMacOSiOS::recordEvent(const QString &event) const
{
    [Countly.sharedInstance recordEvent:event.toNSString()];
}

} // namespace Vremenar
