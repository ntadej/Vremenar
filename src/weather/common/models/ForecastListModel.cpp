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

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

#include "weather/common/models/ForecastListModel.h"

namespace Vremenar
{

ForecastListModel::ForecastListModel(QObject *parent)
    : ListModel(ForecastInfo::roleNames(), parent) {}

void ForecastListModel::generateModel(const QJsonArray &array)
{
    for (const QJsonValue &value : array) {
        QJsonObject data = value.toObject();

        QDateTime time = QDateTime::fromString(data[QStringLiteral("date")].toString(), QStringLiteral("yyyyMMddHHmm"));
        time.setTimeSpec(Qt::UTC);

        appendRow(std::make_unique<ForecastInfo>(
            data[QStringLiteral("path")].toString(),
            time));
    }
}

} // namespace Vremenar
