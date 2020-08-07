/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "weather/common/models/WeatherMapModelBase.h"

namespace Vremenar
{

WeatherMapModelBase::WeatherMapModelBase(QObject *parent)
    : ListModel(WeatherInfo::roleNames(), parent) {}

void WeatherMapModelBase::update(WeatherMapModelBase *model,
                                 qint64 time)
{
    for (int i = 0; i < model->rowCount(); i++) {
        const auto *entry = model->row<WeatherInfo>(i);
        if (entry->time() != time) {
            continue;
        }

        auto *toUpdate = find<WeatherInfo>(entry->id());
        if (toUpdate == nullptr) {
            continue;
        }

        toUpdate->update(entry);
    }

    Q_EMIT dataChanged(index(0), index(rowCount() - 1));
}

} // namespace Vremenar
