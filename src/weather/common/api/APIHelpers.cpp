/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/api/APIHelpers.h"

using namespace Vremenar;

QString API::generateParameters(const QVariantMap &map)
{
    QString out;
    for (QString key : map.keys()) {
        if (!out.isEmpty()) {
            out.append("&");
        }

        out.append(QString("%1=%2").arg(key, map[key].toString()));
    }

    return out;
}
