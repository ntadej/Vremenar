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

#ifndef VREMENAR_MAPLAYERSPROXYMODEL_H_
#define VREMENAR_MAPLAYERSPROXYMODEL_H_

#include <QtCore/QDateTime>
#include <QtCore/QSortFilterProxyModel>

namespace Vremenar
{

class MapLayersProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(qint64 minTimestamp READ minTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 maxTimestamp READ maxTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 stepTimestamp READ stepTimestamp NOTIFY rowCountChanged)

    Q_PROPERTY(qint64 time READ timestamp WRITE setTimestamp NOTIFY timestampChanged)

    Q_PROPERTY(QString url READ url NOTIFY timestampChanged)
    Q_PROPERTY(QVariant coordinates READ coordinates NOTIFY timestampChanged)

public:
    explicit MapLayersProxyModel(QVariant defaultCoordinates,
                                 QObject *parent = nullptr);

    [[nodiscard]] qint64 minTimestamp() const;
    [[nodiscard]] qint64 maxTimestamp() const;
    [[nodiscard]] qint64 stepTimestamp() const;

    [[nodiscard]] inline qint64 timestamp() const { return _time; }
    void setTimestamp(qint64 time);

    [[nodiscard]] inline QString url() const { return _url; }
    [[nodiscard]] inline QVariant coordinates() const { return _coordinates; }

Q_SIGNALS:
    void rowCountChanged();
    void timestampChanged();

protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

private:
    qint64 _time;
    QString _url;
    QVariant _coordinates;
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYERSPROXYMODEL_H_
