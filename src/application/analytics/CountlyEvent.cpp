/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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

namespace Vremenar
{

Countly::Event::Event(const QString &key,
                      int count)
{
    _object[QStringLiteral("key")] = key;
    _object[QStringLiteral("count")] = count;
}

Countly::Event::Event(const QString &key,
                      int count,
                      double sum)
{
    _object[QStringLiteral("key")] = key;
    _object[QStringLiteral("count")] = count;
    _object[QStringLiteral("sum")] = sum;
}

} // namespace Vremenar
