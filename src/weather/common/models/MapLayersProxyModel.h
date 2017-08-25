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

#include "weather/common/Weather.h"

class MapLayersProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(Vremenar::Weather::MapType type READ type WRITE setType)
public:
    explicit MapLayersProxyModel(QObject *parent = nullptr);
    ~MapLayersProxyModel();

    inline Vremenar::Weather::MapType type() const { return _type; }
    void setType(Vremenar::Weather::MapType type);

    inline QDateTime time() const { return QDateTime::fromSecsSinceEpoch(_time); }
    void setTime(const QDateTime &time);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

private:
    Vremenar::Weather::MapType _type;
    qint64 _time;
};

#endif // VREMENAR_MAPLAYERSPROXYMODEL_H_
