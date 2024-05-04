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

#ifndef VREMENAR_ANALYTICSENGINE_H_
#define VREMENAR_ANALYTICSENGINE_H_

#include <QtCore/QString>

namespace Vremenar
{

class AnalyticsEngine
{
    Q_DISABLE_COPY_MOVE(AnalyticsEngine)
public:
    AnalyticsEngine() = default;
    virtual ~AnalyticsEngine() = default;

    [[nodiscard]] virtual bool manualSessionHandling() const = 0;

    virtual void beginSession() const = 0;
    virtual void updateSession() const = 0;
    virtual void endSession() const = 0;

    virtual void recordEvent(const QString &event) const = 0;
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICSENGINE_H_
