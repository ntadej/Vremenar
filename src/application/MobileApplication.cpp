/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "common/Output.h"

#include "application/MobileApplication.h"

namespace Vremenar
{

MobileApplication::MobileApplication(int &argc,
                                     char **argv,
                                     QObject * /* parent */)
    : QGuiApplication(argc, argv)
{
    Output::welcome();
}

MobileApplication MobileApplication::init(int &argc,
                                          char **argv)
{
    return MobileApplication(argc, argv);
}

} // namespace Vremenar
