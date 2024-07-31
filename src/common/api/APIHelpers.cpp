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

#include "common/api/APIHelpers.h"

#include <QtCore/QLatin1StringView>
#include <QtCore/QString>
#include <QtCore/QVariantMap>

using Qt::Literals::StringLiterals::operator""_L1;

namespace Vremenar
{

QString API::generateParameters(const QVariantMap &map)
{
    QString out;
    QVariantMap::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if (!out.isEmpty()) {
            out.append("&"_L1);
        }

        out.append("%1=%2"_L1.arg(i.key(), i.value().toString()));

        ++i;
    }

    return out;
}

} // namespace Vremenar
