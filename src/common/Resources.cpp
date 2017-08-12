/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>

#include "common/Resources.h"

QString Vremenar::Resources::path(const QString &file)
{
    QString path;
    if (resource(file).isEmpty())
        path = QFileInfo(file).absolutePath();
    else
        path = QFileInfo(resource(file)).absolutePath();

    return path;
}

QString Vremenar::Resources::resource(const QString &file)
{
    QString path;

    if (QFileInfo(file).exists())
        path = QFileInfo(file).absoluteFilePath();

    // Try resources application path
    else if (QFileInfo(":/Vremenar/" + file).exists())
        path = QFileInfo(":/Vremenar/" + file).absoluteFilePath();

    // Try application exe working path
    else if (QFileInfo(QDir::currentPath() + "/" + file).exists())
        path = QFileInfo(QDir::currentPath() + "/" + file).absoluteFilePath();

    // Try application exe directory
    else if (QFileInfo(QCoreApplication::applicationDirPath() + "/" + file).exists())
        path = QFileInfo(QCoreApplication::applicationDirPath() + "/" + file).absoluteFilePath();

    // Try application exe directory without src for development
    else if (QFileInfo(QCoreApplication::applicationDirPath().replace("/src", "") + "/" + file).exists())
        path = QFileInfo(QCoreApplication::applicationDirPath().replace("/src", "") + "/" + file).absoluteFilePath();

#if defined(Q_OS_UNIX)
    else if (QFileInfo("/usr/bin/" + file).exists())
        path = QFileInfo("/usr/bin/" + file).absoluteFilePath();
#endif

#if defined(Q_OS_MAC)
    else if (QFileInfo(QCoreApplication::applicationDirPath().replace("MacOS", "Resources") + "/" + file).exists())
        path = QFileInfo(QCoreApplication::applicationDirPath().replace("MacOS", "Resources") + "/" + file).absoluteFilePath();
#endif

    return path;
}

QString Vremenar::Resources::appData()
{
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    return dir.path();
}
