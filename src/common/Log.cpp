/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QMutex>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>

#include "common/Common.h"
#include "common/Log.h"
#include "common/Output.h"
#include "common/Resources.h"

static QTextStream *out;
static QMutex *outMutex;

void Vremenar::Log::output(QtMsgType type,
                           const QMessageLogContext &context,
                           const QString &msg)
{
    Q_UNUSED(context)

    QMutexLocker locker(outMutex);

    QString debugdate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    switch (type) {
    case QtInfoMsg:
        debugdate += " [I]";
        break;
    case QtDebugMsg:
        debugdate += " [D]";
        break;
    case QtWarningMsg:
        debugdate += " [W]";
        break;
    case QtCriticalMsg:
        debugdate += " [C]";
        break;
    case QtFatalMsg:
        debugdate += " [F]";
    }
    (*out) << debugdate << " " << msg << endl;

//#ifdef QT_DEBUG
    Output(true) << debugdate << " " << msg << endl;
//#endif

    if (QtFatalMsg == type) {
        abort();
    }
}

void Vremenar::Log::setup()
{
#if LOGGING
    QString fileName = Vremenar::Resources::appData() + "/" + Vremenar::executable() + ".log";
    QFile *log = new QFile(fileName);
    if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        out = new QTextStream(log);
        outMutex = new QMutex;
        qInstallMessageHandler(output);
    } else {
        qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
    }
#endif
}
