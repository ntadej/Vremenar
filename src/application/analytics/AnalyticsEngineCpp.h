/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_ANALYTICSENGINECPP_H_
#define VREMENAR_ANALYTICSENGINECPP_H_

#include "application/analytics/AnalyticsEngine.h"

#include <memory>

namespace Vremenar
{

class Countly;
class NetworkManager;

class AnalyticsEngineCpp : public AnalyticsEngine
{
    Q_DISABLE_COPY_MOVE(AnalyticsEngineCpp)
public:
    explicit AnalyticsEngineCpp(NetworkManager *network);
    ~AnalyticsEngineCpp() override;

    [[nodiscard]] bool manualSessionHandling() const override { return true; }

    void beginSession() const override;
    void updateSession() const override;
    void endSession() const override;

    void recordEvent(const QString &event) const override;

private:
    std::unique_ptr<Countly> _countly;
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICSENGINECPP_H_
