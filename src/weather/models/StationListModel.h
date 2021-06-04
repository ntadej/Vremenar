/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_STATIONLISTMODEL_H_
#define VREMENAR_STATIONLISTMODEL_H_

#include "common/ListModel.h"

namespace Vremenar
{

class StationListModel : public ListModel
{
    Q_OBJECT
public:
    explicit StationListModel(QObject *parent = nullptr);

    void addStations(const QJsonArray &data);
};

} // namespace Vremenar

#endif // VREMENAR_STATIONLISTMODEL_H_
