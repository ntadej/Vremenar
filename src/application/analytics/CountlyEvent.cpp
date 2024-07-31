/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* Based on https://github.com/Countly/countly-sdk-cpp
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "Countly.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QString>

using Qt::Literals::StringLiterals::operator""_L1;

namespace Vremenar
{

Countly::Event::Event(const QString &key,
                      int count)
{
    _object["key"_L1] = key;
    _object["count"_L1] = count;
}

Countly::Event::Event(const QString &key,
                      int count,
                      double sum)
{
    _object["key"_L1] = key;
    _object["count"_L1] = count;
    _object["sum"_L1] = sum;
}

} // namespace Vremenar
