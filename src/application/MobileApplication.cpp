/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtGui/QFileOpenEvent>

#include "common/Common.h"
#include "common/Log.h"
#include "common/Output.h"

#include "MobileApplication.h"

MobileApplication::MobileApplication(int &argc,
                                     char **argv)
    : QGuiApplication(argc, argv) {}

MobileApplication::~MobileApplication() {}

void MobileApplication::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain());
    QCoreApplication::setApplicationName(Vremenar::name());
    QCoreApplication::setApplicationVersion(Vremenar::version());

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    Vremenar::Log::setup();
}

void MobileApplication::postInit()
{
    Vremenar::Output::welcome();
}
