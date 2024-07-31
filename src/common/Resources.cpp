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

#include "common/Resources.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QLatin1StringView>
#include <QtCore/QStandardPaths>
#include <QtCore/QString>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

QString Resources::path(const QString &file)
{
    QString path;
    if (resource(file).isEmpty()) {
        path = QFileInfo(file).absolutePath();
    } else {
        path = QFileInfo(resource(file)).absolutePath();
    }

    return path;
}

QString Resources::resource(const QString &file)
{
    QString path;

    if (QFileInfo::exists(file)) {
        path = QFileInfo(file).absoluteFilePath();
    }

    // Try resources application path
    else if (QFileInfo::exists(":/Vremenar/" + file)) {
        path = QFileInfo(":/Vremenar/" + file).absoluteFilePath();
    }

    // Try application exe working path
    else if (QFileInfo::exists(QDir::currentPath() + "/" + file)) {
        path = QFileInfo(QDir::currentPath() + "/" + file).absoluteFilePath();
    }

    // Try application exe directory
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath() + "/" + file)) {
        path = QFileInfo(QCoreApplication::applicationDirPath() + "/" + file).absoluteFilePath();
    }

    // Try application exe directory without src for development
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath().remove("/src"_L1) + "/" + file)) {
        path = QFileInfo(QCoreApplication::applicationDirPath().remove("/src"_L1) + "/" + file).absoluteFilePath();
    }

#if defined(Q_OS_UNIX)
    else if (QFileInfo::exists("/usr/bin/" + file)) {
        path = QFileInfo("/usr/bin/" + file).absoluteFilePath();
    }
#endif

#if defined(Q_OS_MACOS)
    else if (QFileInfo::exists(QCoreApplication::applicationDirPath().replace("MacOS"_L1, "Resources"_L1) + "/" + file)) {
        path = QFileInfo(QCoreApplication::applicationDirPath().replace("MacOS"_L1, "Resources"_L1) + "/" + file).absoluteFilePath();
    }
#endif

    return path;
}

QString Resources::appData()
{
    const QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(u"."_s);
    }

    return dir.path();
}

QString Resources::logLocation()
{
#if VREMENAR_MOBILE
    const QDir dir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
#else
    const QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
#endif
    if (!dir.exists()) {
        dir.mkpath(u"."_s);
    }

    return dir.path();
}

} // namespace Vremenar
