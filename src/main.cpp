/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifdef VREMENAR_MOBILE
#include "application/MobileApplication.h"
#else
#include "application/DesktopApplication.h"
#endif

#include "application/ApplicationWindow.h"

int main(int argc, char *argv[])
{
#ifdef VREMENAR_MOBILE
    MobileApplication::preInit();
    MobileApplication instance(argc, argv);
#else
    DesktopApplication::preInit();
    DesktopApplication instance(argc, argv);

    // Is another instance of the program is already running
    if (!instance.shouldContinue())
        return 0;
#endif

    instance.postInit();

    Vremenar::ApplicationWindow main;

    return instance.exec();
}
