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

#include <memory>

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMutex>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

#ifdef Q_OS_ANDROID
#include <android/log.h>
#endif

#include "common/Output.h"
#include "common/Resources.h"

#include "common/Log.h"

#include "Config.h"

namespace Vremenar
{

namespace Log
{
static std::unique_ptr<QTextStream> out;
static std::unique_ptr<QFile> outFile;
static std::unique_ptr<QMutex> outMutex;

#ifdef Q_OS_ANDROID
const static std::string androidName = QString(Vremenar::name).toStdString();
#endif
} // namespace Log

void Log::output(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &msg)
{
    Q_UNUSED(context)

    QMutexLocker locker(outMutex.get());

#ifdef Q_OS_ANDROID
    android_LogPriority priority = ANDROID_LOG_DEFAULT;
#endif

    QString debugdate = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    switch (type) {
    case QtInfoMsg:
        debugdate += QStringLiteral(" [I]");
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_INFO;
#endif
        break;
    case QtDebugMsg:
        debugdate += QStringLiteral(" [D]");
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_DEBUG;
#endif
        break;
    case QtWarningMsg:
        debugdate += QStringLiteral(" [W]");
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_WARN;
#endif
        break;
    case QtCriticalMsg:
        debugdate += QStringLiteral(" [C]");
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_ERROR;
#endif
        break;
    case QtFatalMsg:
        debugdate += QStringLiteral(" [F]");
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_FATAL;
#endif
        break;
    }
    (*out) << debugdate << QStringLiteral(" ") << msg << Qt::endl;

    //#ifdef QT_DEBUG
    Output(true) << debugdate << QStringLiteral(" ") << msg << Qt::endl;
    //#endif

#ifdef Q_OS_ANDROID
    __android_log_write(priority, androidName.c_str(), (debugdate + QStringLiteral(" ") + msg).toStdString().c_str());
#endif

    if (QtFatalMsg == type) {
        abort();
    }
}

void Log::setup()
{
    if (Vremenar::loggingEnabled) {
        QString fileName = Resources::logLocation() + "/" + Vremenar::name + ".log";
        outFile = std::make_unique<QFile>(fileName);
        if (outFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            out = std::make_unique<QTextStream>(outFile.get());
            outMutex = std::make_unique<QMutex>();
            qInstallMessageHandler(output);
        } else {
            qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
        }
    }
}

} // namespace Vremenar
