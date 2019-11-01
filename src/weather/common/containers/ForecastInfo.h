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

#ifndef VREMENAR_FORECASTINFO_H_
#define VREMENAR_FORECASTINFO_H_

#include <QtCore/QDateTime>

#include "common/ListItem.h"

namespace Vremenar
{

class ForecastInfo : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QDateTime time READ time CONSTANT)
public:
    enum Roles {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        UrlRole,
        TimeRole
    };

    explicit ForecastInfo(QString url,
                          QDateTime time,
                          QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] inline QString url() const { return _url; }
    [[nodiscard]] inline QDateTime time() const { return _time; }

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {UrlRole, "url"},
            {TimeRole, "time"}};
    }

private:
    QString _url;
    QDateTime _time;
};

} // namespace Vremenar

#endif // VREMENAR_FORECASTINFO_H_
