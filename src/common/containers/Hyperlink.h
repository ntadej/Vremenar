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

#ifndef VREMENAR_HYPERLINK_H_
#define VREMENAR_HYPERLINK_H_

#include "common/ListItem.h"

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include <cstdint>

namespace Vremenar
{

class Hyperlink : public ListItem
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display CONSTANT)
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(bool mobileOnly READ mobileOnly CONSTANT)
public:
    enum Roles : std::uint16_t {
        DisplayRole = Qt::DisplayRole,
        IdRole = Qt::UserRole + 1,
        UrlRole,
        MobileOnlyRole
    };

    explicit Hyperlink(QString title,
                       QUrl url,
                       QObject *parent = nullptr);

    explicit Hyperlink(QString title,
                       QUrl url,
                       bool mobileOnly,
                       QObject *parent = nullptr);

    // Implemented virtual functions
    [[nodiscard]] QVariant data(int role) const final;
    [[nodiscard]] QString display() const final;

    [[nodiscard]] const QUrl &url() const { return _url; }
    [[nodiscard]] bool mobileOnly() const { return _mobileOnly; }

    [[nodiscard]] QJsonObject asJson() const;
    [[nodiscard]] QString asHtml(const QString &style = QString()) const;

    static QHash<int, QByteArray> roleNames()
    {
        return {
            {IdRole, "id"},
            {DisplayRole, "display"},
            {UrlRole, "url"},
            {MobileOnlyRole, "mobileOnly"}};
    }

private:
    QString _title;
    QUrl _url;
    bool _mobileOnly;
};

} // namespace Vremenar

#endif // VREMENAR_HYPERLINK_H_
