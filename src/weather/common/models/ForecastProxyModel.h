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

#ifndef VREMENAR_FORECASTPROXYMODEL_H_
#define VREMENAR_FORECASTPROXYMODEL_H_

#include <QtCore/QDateTime>
#include <QtCore/QSortFilterProxyModel>

namespace Vremenar
{

class ForecastProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(qreal zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged)
public:
    explicit ForecastProxyModel(QObject *parent = nullptr);

    [[nodiscard]] inline qreal zoomLevel() const { return _zoomLevel; }
    void setZoomLevel(qreal level);

Q_SIGNALS:
    void rowCountChanged();
    void zoomLevelChanged();

protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

private:
    qreal _zoomLevel{};
};

} // namespace Vremenar

#endif // VREMENAR_FORECASTPROXYMODEL_H_
