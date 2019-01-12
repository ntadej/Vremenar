/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ENUMS_H_
#define VREMENAR_ENUMS_H_

#include <QtCore/QObject>

namespace Vremenar
{

class Common
{
    Q_GADGET
public:
    enum DeviceType {
        Desktop,
        iPhone,
        iPad,
        UnknownDevice
    };

    Q_ENUM(DeviceType)
};

} // namespace Vremenar

#endif // VREMENAR_ENUMS_H_
