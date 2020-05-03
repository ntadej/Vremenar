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

#ifndef VREMENAR_ANALYTICSENGINEMACOSIOS_H_
#define VREMENAR_ANALYTICSENGINEMACOSIOS_H_

#include "application/analytics/AnalyticsEngine.h"

namespace Vremenar
{

class AnalyticsEngineMacOSiOS : public AnalyticsEngine
{
public:
    AnalyticsEngineMacOSiOS();

    void recordEvent(const QString &event) const override;
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICSENGINEMACOSIOS_H_
