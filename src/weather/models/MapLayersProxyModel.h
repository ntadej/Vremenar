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

#ifndef VREMENAR_MAPLAYERSPROXYMODEL_H_
#define VREMENAR_MAPLAYERSPROXYMODEL_H_

#include "weather/Weather.h"

#include <QtCore/QAbstractItemModel>
#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QVariant>

#include <memory>

namespace Vremenar
{

class MapLayersProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 minTimestamp READ minTimestamp NOTIFY rowCountChanged)
    Q_PROPERTY(qint64 maxTimestamp READ maxTimestamp NOTIFY rowCountChanged)

    Q_PROPERTY(int index READ currentIndex WRITE setCurrentIndex NOTIFY timestampChanged)
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

    [[nodiscard]] int currentIndex() const;
    void setCurrentIndex(int newIndex);
    [[nodiscard]] qint64 timestamp() const;
    void setTimestamp(qint64 time);
    [[nodiscard]] QString day() const;
    [[nodiscard]] bool dayHighlighted() const;
    [[nodiscard]] bool daily() const { return _daily; };

    [[nodiscard]] QString title() const;
    [[nodiscard]] Weather::MapType type() const { return _type; }
    [[nodiscard]] Weather::MapRenderingType renderingType() const { return _renderingType; }
    [[nodiscard]] const QVariant &coordinates() const { return _coordinates; }

    [[nodiscard]] bool animated() const { return _animated; }

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
    void mapChanged(Weather::MapType,          // NOLINT(readability-named-parameter)
                    Weather::MapRenderingType, // NOLINT(readability-named-parameter)
                    const QString &,           // NOLINT(readability-named-parameter)
                    const QString &,           // NOLINT(readability-named-parameter)
                    const QString &);          // NOLINT(readability-named-parameter)

private slots:
    void setDefaultTimestamp();

private:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

    std::unique_ptr<QTimer> _timer;
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
