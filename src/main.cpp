/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "application/DesktopApplication.h"
#include "application/ApplicationWindow.h"

int main(int argc, char *argv[])
{
    DesktopApplication::preInit();

    DesktopApplication instance(argc, argv);
    // Is another instance of the program is already running
    if (!instance.shouldContinue())
        return 0;

    instance.postInit();

    ApplicationWindow main;

    QObject::connect(&instance, &DesktopApplication::activate, &main, &ApplicationWindow::activate);
    QObject::connect(&instance, &DesktopApplication::dockClicked, &main, &ApplicationWindow::dockClicked);
    QObject::connect(&instance, &DesktopApplication::urlOpened, &main, &ApplicationWindow::processUrl);

    return instance.exec();
}
