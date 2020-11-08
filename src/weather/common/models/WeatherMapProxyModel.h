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

#ifndef VREMENAR_WEATHERMAPPROXYMODEL_H_
#define VREMENAR_WEATHERMAPPROXYMODEL_H_

#include <memory>

#include <QtCore/QDateTime>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QTimer>
#include <QtPositioning/QGeoShape>

namespace Vremenar
{

class WeatherMapProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(qreal zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged)
    Q_PROPERTY(QGeoShape visibleRegion READ visibleRegion WRITE setVisibleRegion NOTIFY visibleRegionChanged)
    Q_PROPERTY(qint64 time READ time NOTIFY timeChanged)

public:
    explicit WeatherMapProxyModel(QObject *parent = nullptr);

    [[nodiscard]] inline qreal zoomLevel() const { return _zoomLevel; }
    void setZoomLevel(qreal level);
    [[nodiscard]] inline const QGeoShape &visibleRegion() const { return _visibleRegion; }
    void setVisibleRegion(const QGeoShape &shape);
    [[nodiscard]] inline qint64 time() const { return _time; }
    void setTime(qint64 time);

Q_SIGNALS:
    void rowCountChanged();
    void zoomLevelChanged();
    void visibleRegionChanged();
    void timeChanged();

private:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

    qreal _zoomLevel{};
    QGeoShape _visibleRegion{};
    qint64 _time{};

    std::unique_ptr<QTimer> _timer{};
};

} // namespace Vremenar

#endif // VREMENAR_WEATHERMAPPROXYMODEL_H_
