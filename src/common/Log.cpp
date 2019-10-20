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

#include <memory>

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMutex>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

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
} // namespace Log

void Log::output(QtMsgType type,
                 const QMessageLogContext &context,
                 const QString &msg)
{
    Q_UNUSED(context)

    QMutexLocker locker(outMutex.get());

    QString debugdate = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd hh:mm:ss"));
    switch (type) {
    case QtInfoMsg:
        debugdate += QStringLiteral(" [I]");
        break;
    case QtDebugMsg:
        debugdate += QStringLiteral(" [D]");
        break;
    case QtWarningMsg:
        debugdate += QStringLiteral(" [W]");
        break;
    case QtCriticalMsg:
        debugdate += QStringLiteral(" [C]");
        break;
    case QtFatalMsg:
        debugdate += QStringLiteral(" [F]");
    }
    (*out) << debugdate << QStringLiteral(" ") << msg << endl;

    //#ifdef QT_DEBUG
    Output(true) << debugdate << QStringLiteral(" ") << msg << endl;
    //#endif

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
