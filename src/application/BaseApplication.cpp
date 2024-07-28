/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/BaseApplication.h"

#include "common/Log.h"

#include "Config.h"

#include <QtCore/QCoreApplication>
#include <QtNetwork/QSslConfiguration>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGRendererInterface>

#include <stdexcept>

namespace Vremenar
{

void Application::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain);
    QCoreApplication::setApplicationName(Vremenar::name);
    QCoreApplication::setApplicationVersion(Vremenar::version);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

#if defined(Q_OS_WINDOWS)
    // qputenv("QT_QPA_PLATFORM", "windows:darkmode=1");
#elif defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
    qputenv("QT_GEOCLUE_APP_DESKTOP_ID", QString(Vremenar::appID).toUtf8());
#endif

#if !defined(Q_OS_IOS)
    // Certificates
    auto cfg = QSslConfiguration::defaultConfiguration();
    if (!cfg.addCaCertificates(":/certificates/isrgrootx1.pem") || !cfg.addCaCertificates(":/certificates/isrg-root-x2.pem")) {
        throw std::runtime_error("Failed to add certificates");
    }

    QSslConfiguration::setDefaultConfiguration(cfg);
#endif

    Log::setup();
}

} // namespace Vremenar
