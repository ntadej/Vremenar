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
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>

#include "common/Resources.h"

namespace Vremenar
{

QString Resources::path(const QString &file)
{
    QString path;
    if (resource(file).isEmpty())
        path = QFileInfo(file).absolutePath();
    else
        path = QFileInfo(resource(file)).absolutePath();

    return path;
}

QString Resources::resource(const QString &file)
{
    QString path;

    if (QFileInfo::exists(file))
        path = QFileInfo(file).absoluteFilePath();

    // Try resources application path
    else if (QFileInfo::exists(":/Vremenar/" + file))
        path = QFileInfo(":/Vremenar/" + file).absoluteFilePath();

    // Try application exe working path
    else if (QFileInfo::exists(QDir::currentPath() + "/" + file))
        path = QFileInfo(QDir::currentPath() + "/" + file).absoluteFilePath();

    // Try application exe directory
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath() + "/" + file))
        path = QFileInfo(QCoreApplication::applicationDirPath() + "/" + file).absoluteFilePath();

    // Try application exe directory without src for development
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath().replace("/src", "") + "/" + file))
        path = QFileInfo(QCoreApplication::applicationDirPath().replace("/src", "") + "/" + file).absoluteFilePath();

#if defined(Q_OS_UNIX)
    else if (QFileInfo::exists("/usr/bin/" + file))
        path = QFileInfo("/usr/bin/" + file).absoluteFilePath();
#endif

#if defined(Q_OS_MACOS)
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath().replace("MacOS", "Resources") + "/" + file))
        path = QFileInfo(QCoreApplication::applicationDirPath().replace("MacOS", "Resources") + "/" + file).absoluteFilePath();
#endif

    return path;
}

QString Resources::appData()
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.path();
}

QString Resources::logLocation()
{
#if VREMENAR_MOBILE
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
#else
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
#endif
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.path();
}

} // namespace Vremenar
