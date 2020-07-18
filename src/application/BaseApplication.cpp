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

#include <QtCore/QCoreApplication>

#include "application/BaseApplication.h"
#include "common/Log.h"

#include "Config.h"

namespace Vremenar
{

void Application::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain);
#if defined(Q_OS_MACOS) && defined(QT_DEBUG)
    QCoreApplication::setApplicationName("VremenarDevel");
#else
    QCoreApplication::setApplicationName(Vremenar::name);
#endif
    QCoreApplication::setApplicationVersion(Vremenar::version);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

#ifdef Q_OS_LINUX
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
#endif

    Log::setup();
}

} // namespace Vremenar
