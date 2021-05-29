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

#ifndef VREMENAR_LOCATION_H_
#define VREMENAR_LOCATION_H_

#include <QtCore/QObject>

namespace Vremenar::Location
{

Q_NAMESPACE

enum Source {
    Automatic,
    Station,
    Coordinate,
    Disabled,
};

Q_ENUM_NS(Source)

} // namespace Vremenar::Location

#endif // VREMENAR_LOCATION_H_
