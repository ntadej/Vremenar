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

#include "common/api/APIHelpers.h"

namespace Vremenar
{

QString API::generateParameters(const QVariantMap &map)
{
    QString out;
    QVariantMap::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if (!out.isEmpty()) {
            out.append(QStringLiteral("&"));
        }

        out.append(QStringLiteral("%1=%2").arg(i.key(), i.value().toString()));

        ++i;
    }

    return out;
}

} // namespace Vremenar
