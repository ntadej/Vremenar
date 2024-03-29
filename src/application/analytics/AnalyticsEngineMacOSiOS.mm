/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
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
    // NOLINTNEXTLINE(misc-const-correctness)
    CountlyConfig *config = [[CountlyConfig alloc] init];
    // NOLINTNEXTLINE(clang-analyzer-nullability.NullPassedToNonnull,clang-analyzer-nullability.NullablePassedToNonnull,clang-analyzer-nullability.NullabilityBase)
    config.appKey = [NSString stringWithUTF8String:Vremenar::CountlyAppKey.data()];
    config.host = [NSString stringWithUTF8String:Vremenar::CountlyEndpoint.data()];
    config.secretSalt = [NSString stringWithUTF8String:Vremenar::CountlySalt.data()];
    config.features = @[ CLYCrashReporting ];
#ifdef Q_OS_MACOS
    config.manualSessionHandling = YES;
#endif
#ifdef QT_DEBUG
    config.enableDebug = YES;
#endif
    [Countly.sharedInstance startWithConfig:config];

    [config release];
}

bool AnalyticsEngineMacOSiOS::manualSessionHandling() const
{
#ifdef Q_OS_MACOS
    return true;
#else
    return false;
#endif
}

void AnalyticsEngineMacOSiOS::beginSession() const
{
    [Countly.sharedInstance beginSession];
}

void AnalyticsEngineMacOSiOS::updateSession() const
{
    [Countly.sharedInstance updateSession];
}

void AnalyticsEngineMacOSiOS::endSession() const
{
    [Countly.sharedInstance endSession];
}

void AnalyticsEngineMacOSiOS::recordEvent(const QString &event) const
{
    [Countly.sharedInstance recordEvent:event.toNSString()];
}

} // namespace Vremenar
