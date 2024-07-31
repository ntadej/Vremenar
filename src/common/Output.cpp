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

#include "common/Output.h"

#include "Config.h"

#include <QtCore/QDate>
#include <QtCore/QIODevice>
#include <QtCore/QString>

#include <cstdio>

using Qt::Literals::StringLiterals::operator""_s;

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
    Output() << u"%1 %2"_s.arg(Vremenar::name, Vremenar::version) << Qt::endl
             << u"Copyright (C) %1 Tadej Novak"_s.arg(QDate::currentDate().year()) << Qt::endl
             << Qt::endl;
}

} // namespace Vremenar
