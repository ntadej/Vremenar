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

    Q_PROPERTY(Weather::MapRenderingType type READ type NOTIFY typeChanged)
    Q_PROPERTY(QString title READ title NOTIFY timestampChanged)
    Q_PROPERTY(QString url READ url NOTIFY timestampChanged)
    Q_PROPERTY(QString image READ image NOTIFY imageChanged)
    Q_PROPERTY(QVariant coordinates READ coordinates NOTIFY timestampChanged)

    Q_PROPERTY(bool animated READ animated NOTIFY animatedChanged)

public:
    explicit MapLayersProxyModel(QObject *parent = nullptr);

    [[nodiscard]] qint64 minTimestamp() const;
    [[nodiscard]] qint64 maxTimestamp() const;

    [[nodiscard]] qint64 timestamp() const;
    void setTimestamp(qint64 time);
    [[nodiscard]] QString day() const;

    QString title() const;
    [[nodiscard]] inline Weather::MapRenderingType type() const { return _type; }
    [[nodiscard]] inline const QString &url() const { return _url; }
    [[nodiscard]] inline const QString &image() const { return _image; }
    void setImage(const QString &image);
    [[nodiscard]] inline const QVariant &coordinates() const { return _coordinates; }

    [[nodiscard]] inline bool animated() const { return _animated; }

    void setUpdating(bool updating,
                     bool silent = false);

    Q_INVOKABLE void previous();
    Q_INVOKABLE void next();
    Q_INVOKABLE void nextTimer();
    Q_INVOKABLE void play();
    Q_INVOKABLE void playResume();

Q_SIGNALS:
    void rowCountChanged();
    void timestampChanged();
    void imageChanged();
    void animatedChanged();
    void typeChanged(Weather::MapRenderingType,
                     const QString &);

private Q_SLOTS:
    void setDefaultTimestamp();

private:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const override;

    std::unique_ptr<QTimer> _timer{};
    bool _animated{false};
    bool _updating{false};

    qint64 _time{};
    Weather::MapRenderingType _type{Weather::ImageRendering};
    QString _url;
    QString _image{Weather::blankPng};
    QVariant _coordinates;
    int _row{};
};

} // namespace Vremenar

#endif // VREMENAR_MAPLAYERSPROXYMODEL_H_
