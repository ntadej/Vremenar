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

#ifndef VREMENAR_MAPLEGENDPROXYMODEL_H_
#define VREMENAR_MAPLEGENDPROXYMODEL_H_

#include <QtCore/QSortFilterProxyModel>

#include "weather/common/Weather.h"

namespace Vremenar
{

class MapLegendProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Weather::MapType type READ type WRITE setType NOTIFY typeChanged)

public:
    explicit MapLegendProxyModel(QObject *parent = nullptr);

    inline Weather::MapType type() const { return _type; }
    void setType(Weather::MapType type);

Q_SIGNALS:
    void typeChanged();

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

private:
    Weather::MapType _type{Weather::UnknownMap};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDPROXYMODEL_H_
