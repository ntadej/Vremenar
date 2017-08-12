/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDate>
#include <QtCore/QTextCodec>

#include "common/Common.h"
#include "common/Output.h"

using namespace Vremenar;

Output::Output(bool error)
    : QTextStream(error ? stderr : stdout, QIODevice::WriteOnly) {}

Output::~Output() {}

Output &Output::operator<<(const QString &string)
{
    QTextStream::operator<<(string);

    flush();

    return *this;
}

void Output::welcome()
{
    Output() << QString("%1 %2").arg(Vremenar::name(), Vremenar::version()) << endl
             << QString("Copyright (C) %1 Tadej Novak").arg(QDate::currentDate().year()) << endl
             << endl;
}
