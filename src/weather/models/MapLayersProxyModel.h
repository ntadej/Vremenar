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

#ifndef VREMENAR_MAPLAYERSPROXYMODEL_H_
#define VREMENAR_MAPLAYERSPROXYMODEL_H_

#include <memory>

#include <QtCore/QDateTime>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QTimer>

#include "weather/Weather.h"

namespace Vremenar
{

class MapLayersProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(qint64 minTimestamp READ minTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 maxTimestamp READ maxTimestamp NOTIFY rowCountChanged)

    Q_PROPERTY(qint64 time READ timestamp WRITE setTimestamp NOTIFY timestampChanged)
    Q_PROPERTY(QString day READ day NOTIFY timestampChanged)
    Q_PROPERTY(bool dayHighlighted READ dayHighlighted NOTIFY timestampChanged)
    Q_PROPERTY(bool daily READ daily NOTIFY timestampChanged)

    Q_PROPERTY(Weather::MapType type READ type NOTIFY mapChanged)
    Q_PROPERTY(Weather::MapRenderingType renderingType READ renderingType NOTIFY mapChanged)
    Q_PROPERTY(QString title READ title NOTIFY timestampChanged)
    Q_PROPERTY(QVariant coordinates READ coordinates NOTIFY timestampChanged)

    Q_PROPERTY(bool animated READ animated NOTIFY animatedChanged)

public:
    explicit MapLayersProxyModel(QObject *parent = nullptr);

    [[nodiscard]] qint64 minTimestamp() const;
    [[nodiscard]] qint64 maxTimestamp() const;

    [[nodiscard]] qint64 timestamp() const;
    void setTimestamp(qint64 time);
    [[nodiscard]] QString day() const;
    [[nodiscard]] bool dayHighlighted() const;
    [[nodiscard]] inline bool daily() const { return _daily; };

    [[nodiscard]] QString title() const;
    [[nodiscard]] inline Weather::MapType type() const { return _type; }
    [[nodiscard]] inline Weather::MapRenderingType renderingType() const { return _renderingType; }
    [[nodiscard]] inline const QVariant &coordinates() const { return _coordinates; }

    [[nodiscard]] inline bool animated() const { return _animated; }

    void setUpdating(bool updating,
                     bool silent = false);
    void emitUpdate();

    Q_INVOKABLE void first();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void next();
    Q_INVOKABLE void nextTimer();
    Q_INVOKABLE void last();
    Q_INVOKABLE void play();
    Q_INVOKABLE void playResume();

signals:
    void rowCountChanged();
    void timestampChanged();
    void imageChanged();
    void animatedChanged();
    void mapChanged(Weather::MapType,
                    Weather::MapRenderingType,
                    const QString &,
                    const QString &,
                    const QString &);

private slots:
    void setDefaultTimestamp();

private:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

    std::unique_ptr<QTimer> _timer{};
    bool _animated{false};
    bool _updating{false};

    qint64 _time{};
    qint64 _timeDefault{};
    bool _daily{};
    Weather::MapType _type{Weather::UnknownMapType};
    Weather::MapRenderingType _renderingType{Weather::ImageRendering};
    QVariant _coordinates;
    int _row{};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYERSPROXYMODEL_H_
