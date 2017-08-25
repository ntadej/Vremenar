/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MAPLAYERSPROXYMODEL_H_
#define VREMENAR_MAPLAYERSPROXYMODEL_H_

#include <QtCore/QDateTime>
#include <QtCore/QSortFilterProxyModel>

class MapLayersProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(qint64 time READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(qint64 minTimestamp READ minTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 maxTimestamp READ maxTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 stepTimestamp READ stepTimestamp NOTIFY rowCountChanged)

public:
    explicit MapLayersProxyModel(QObject *parent = nullptr);
    ~MapLayersProxyModel();

    inline QDateTime time() const { return QDateTime::fromSecsSinceEpoch(_time); }
    inline qint64 timestamp() const { return _time; }
    void setTime(const QDateTime &time);
    void setTimestamp(qint64 time);

    qint64 minTimestamp() const;
    qint64 maxTimestamp() const;
    qint64 stepTimestamp() const;

signals:
    void rowCountChanged();
    void timestampChanged();

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

private:
    qint64 _time;
};

#endif // VREMENAR_MAPLAYERSPROXYMODEL_H_
