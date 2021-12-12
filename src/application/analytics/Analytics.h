/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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
#include <QtCore/QTimer>

#include "application/analytics/AnalyticsEngine.h"

namespace Vremenar
{

class NetworkManager;

class Analytics : public QObject
{
    Q_OBJECT
public:
    explicit Analytics(NetworkManager *network,
                       QObject *parent = nullptr);

    enum EventType {
        MapStyleChanged,
        MapTypeChanged
    };

    Q_ENUM(EventType)

    static QString eventString(EventType type,
                               const QString &payload);

public slots:
    void beginSession();
    void updateSession();
    void endSession();

    void recordEvent(Vremenar::Analytics::EventType type,
                     const QString &payload) const;

private:
    std::unique_ptr<AnalyticsEngine> _engine{};
    std::unique_ptr<QTimer> _timer{};
};

} // namespace Vremenar

#endif // VREMENAR_ANALYTICS_H_
