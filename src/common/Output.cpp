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

#include <QtCore/QDate>
#include <QtCore/QTextCodec>

#include "common/Output.h"

#include "Config.h"

namespace Vremenar
{

Output::Output(bool error)
    : QTextStream(error ? stderr : stdout, QIODevice::WriteOnly) {}

Output &Output::operator<<(const QString &string)
{
    QTextStream::operator<<(string);

    flush();

    return *this;
}

void Output::welcome()
{
    Output() << QStringLiteral("%1 %2").arg(Vremenar::name, Vremenar::version) << endl
             << QStringLiteral("Copyright (C) %1 Tadej Novak").arg(QDate::currentDate().year()) << endl
             << endl;
}

} // namespace Vremenar
