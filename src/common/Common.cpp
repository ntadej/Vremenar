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

#include "common/Common.h"

#include "Config.h"

namespace Vremenar
{

QString name()
{
    return "Vremenar";
}

QString executable()
{
#if defined(Q_OS_LINUX)
    return name().toLower();
#else
    return name();
#endif
}

QString domain()
{
    return "tano.si";
}

QString localServer()
{
    return QString(name() + "localserver").toLower();
}

QString version()
{
    return QString(VREMENAR_VERSION);
}

int build()
{
    return VREMENAR_VERSION_BUILD;
}

} // namespace Vremenar
