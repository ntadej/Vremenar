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

#ifndef VREMENAR_MAPLEGENDPROXYMODEL_H_
#define VREMENAR_MAPLEGENDPROXYMODEL_H_

#include "weather/Weather.h"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>

namespace Vremenar
{

class MapLegendProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Weather::MapType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(bool wide READ wide NOTIFY rowCountChanged)
    Q_PROPERTY(bool textBased READ textBased NOTIFY rowCountChanged)

public:
    explicit MapLegendProxyModel(QObject *parent = nullptr);

    [[nodiscard]] Weather::MapType type() const { return _type; }
    void setType(Weather::MapType type);
    [[nodiscard]] bool wide() const;
    [[nodiscard]] bool textBased() const;

signals:
    void rowCountChanged();
    void typeChanged();

protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

private:
    Weather::MapType _type{Weather::UnknownMapType};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLEGENDPROXYMODEL_H_
