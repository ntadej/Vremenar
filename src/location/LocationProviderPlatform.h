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

#ifndef VREMENAR_LOCATIONPROVIDERPLATFORM_H_
#define VREMENAR_LOCATIONPROVIDERPLATFORM_H_

#include <QtCore/QObject>

namespace Vremenar
{

class LocationProvider;

class LocationProviderPlatform
{
    Q_DISABLE_COPY_MOVE(LocationProviderPlatform)

public:
    LocationProviderPlatform() = default;
    virtual ~LocationProviderPlatform() = default;

    [[nodiscard]] virtual bool servicesEnabled() const = 0;
    [[nodiscard]] virtual bool servicesAllowed() const = 0;
};

} // namespace Vremenar

#endif // VREMENAR_LOCATIONPROVIDERPLATFORM_H_
