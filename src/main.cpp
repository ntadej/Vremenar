/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/BaseApplication.h"
#ifdef VREMENAR_MOBILE
#include "application/MobileApplication.h"
#else
#include "application/DesktopApplication.h"
#endif

#include "application/ApplicationWindow.h"

int main(int argc, char *argv[])
{
    Vremenar::Application::preInit();

#ifndef VREMENAR_MOBILE
    // Is another instance of the program already running?
    if (!Vremenar::DesktopApplication::shouldContinue()) {
        return 0;
    }
#endif

#ifdef VREMENAR_MOBILE
    auto instance = Vremenar::MobileApplication::init(argc, argv);
#else
    auto instance = Vremenar::DesktopApplication::init(argc, argv);
#endif
    const Vremenar::ApplicationWindow main;

    return instance.exec(); // NOLINT(readability-static-accessed-through-instance)
}
