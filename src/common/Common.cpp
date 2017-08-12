/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/Common.h"

QString Vremenar::name()
{
    return "Vremenar";
}

QString Vremenar::executable()
{
#if defined(Q_OS_LINUX)
    return name().toLower();
#else
    return name();
#endif
}

QString Vremenar::domain()
{
    return "tano.si";
}

QString Vremenar::localServer()
{
    return QString(name() + "localserver").toLower();
}

QString Vremenar::version()
{
    return QString(VERSION);
}

int Vremenar::build()
{
    return VERSION_BUILD;
}
