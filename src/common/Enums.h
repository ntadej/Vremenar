/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_ENUMS_H_
#define VREMENAR_ENUMS_H_

#include <QtCore/QObject>

namespace Vremenar::Common
{

Q_NAMESPACE

enum DeviceType {
    Desktop,
    iPhone,
    iPad,
    Android,
    AndroidTV,
    DebuggingDevice,
    UnknownDevice
};

Q_ENUM_NS(DeviceType)

} // namespace Vremenar::Common

#endif // VREMENAR_ENUMS_H_
