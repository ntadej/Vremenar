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

#ifndef VREMENAR_ANALYTICS_H_
#define VREMENAR_ANALYTICS_H_

#include <memory>

#include <QtCore/QObject>

#include "application/analytics/AnalyticsEngine.h"

namespace Vremenar
{

class Analytics : public QObject
{
    Q_OBJECT
public:
    explicit Analytics(QObject *parent = nullptr);

    enum EventType {
        MapTypeChanged
    };

    Q_ENUM(EventType)

    static QString eventString(EventType type,
                               const QString &payload);

public Q_SLOTS:
    void recordEvent(Vremenar::Analytics::EventType type,
                     const QString &payload) const;

private:
    std::unique_ptr<AnalyticsEngine> _engine{};
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICS_H_