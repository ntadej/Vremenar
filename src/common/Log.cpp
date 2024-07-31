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

#include "common/Log.h"

#include "common/Output.h"
#include "common/Resources.h"

#include "Config.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QLatin1StringView>
#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QTextStream>

#ifdef Q_OS_ANDROID
#include <android/log.h>
#endif

#include <cstdlib>
#include <memory>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

namespace Log
{
static std::unique_ptr<QTextStream> out; // clazy:exclude=non-pod-global-static NOLINT(cppcoreguidelines-avoid-non-const-global-variables,misc-use-anonymous-namespace)
static std::unique_ptr<QFile> outFile;   // clazy:exclude=non-pod-global-static NOLINT(cppcoreguidelines-avoid-non-const-global-variables,misc-use-anonymous-namespace)
static std::unique_ptr<QMutex> outMutex; // clazy:exclude=non-pod-global-static NOLINT(cppcoreguidelines-avoid-non-const-global-variables,misc-use-anonymous-namespace)

#ifdef Q_OS_ANDROID
const static std::string androidName = QString(Vremenar::name).toStdString(); // clazy:exclude=non-pod-global-static
#endif
} // namespace Log

void Log::output(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &msg)
{
    Q_UNUSED(context)

    const QMutexLocker locker(outMutex.get());

#ifdef Q_OS_ANDROID
    android_LogPriority priority = ANDROID_LOG_DEFAULT;
#endif

    QString debugdate = QDateTime::currentDateTime().toString(u"yyyy-MM-dd hh:mm:ss"_s);
    switch (type) {
    case QtInfoMsg:
        debugdate += " [I]"_L1;
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_INFO;
#endif
        break;
    case QtDebugMsg:
        debugdate += " [D]"_L1;
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_DEBUG;
#endif
        break;
    case QtWarningMsg:
        debugdate += " [W]"_L1;
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_WARN;
#endif
        break;
    case QtCriticalMsg:
        debugdate += " [C]"_L1;
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_ERROR;
#endif
        break;
    case QtFatalMsg:
        debugdate += " [F]"_L1;
#ifdef Q_OS_ANDROID
        priority = ANDROID_LOG_FATAL;
#endif
        break;
    }
    (*out) << debugdate << " "_L1 << msg << Qt::endl;

    //#ifdef QT_DEBUG
    Output(true) << debugdate << " "_L1 << msg << Qt::endl;
    //#endif

#ifdef Q_OS_ANDROID
    __android_log_write(priority, androidName.c_str(), (debugdate + " "_L1 + msg).toStdString().c_str());
#endif

    if (QtFatalMsg == type) {
        abort();
    }
}

void Log::setup()
{
    if (Vremenar::loggingEnabled) {
        const QString fileName = Resources::logLocation() + "/" + Vremenar::name + ".log";
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
