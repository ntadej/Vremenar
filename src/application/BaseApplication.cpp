/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QCoreApplication>

#include "common/Common.h"
#include "common/Log.h"

#include "application/BaseApplication.h"

namespace Vremenar
{

void Application::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain());
    QCoreApplication::setApplicationName(Vremenar::name());
    QCoreApplication::setApplicationVersion(Vremenar::version());

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    Log::setup();
}

} // namespace Vremenar
