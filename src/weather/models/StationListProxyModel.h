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

#ifndef VREMENAR_STATIONLISTPROXYMODEL_H_
#define VREMENAR_STATIONLISTPROXYMODEL_H_

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>

namespace Vremenar
{

class StationListProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(bool ignoreForecastOnly READ ignoreForecastOnly WRITE setIgnoreForecastOnly NOTIFY ignoreForecastOnlyChanged)

public:
    explicit StationListProxyModel(QObject *parent = nullptr);

    [[nodiscard]] bool ignoreForecastOnly() const { return _ignoreForecastOnly; }
    void setIgnoreForecastOnly(bool ignoreForecastOnly);

signals:
    void ignoreForecastOnlyChanged();

private:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

    bool _ignoreForecastOnly{};
};

} // namespace Vremenar

#endif // VREMENAR_STATIONLISTPROXYMODEL_H_
