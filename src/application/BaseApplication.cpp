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

#include <QtCore/QCoreApplication>

#include "application/BaseApplication.h"
#include "common/Log.h"

#include "Config.h"

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQuick/QQuickWindow>
#endif

namespace Vremenar
{

void Application::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain);
    QCoreApplication::setApplicationName(Vremenar::name);
    QCoreApplication::setApplicationVersion(Vremenar::version);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
#else
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

#if defined(Q_OS_WINDOWS)
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#elif defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    qputenv("QT_GEOCLUE_APP_DESKTOP_ID", QString(Vremenar::appID).toUtf8());
#endif

    Log::setup();
}

} // namespace Vremenar
