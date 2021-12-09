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

#include <QtCore/QJsonObject>

#include "common/containers/Hyperlink.h"

namespace Vremenar
{

Hyperlink::Hyperlink(QString title,
                     QUrl url,
                     bool mobileOnly,
                     QObject *parent)
    : ListItem(parent),
      _title(std::move(title)),
      _url(std::move(url)),
      _mobileOnly(mobileOnly)
{
    setId(_url.toString());
}

Hyperlink::Hyperlink(QString title,
                     QUrl url,
                     QObject *parent)
    : ListItem(parent),
      _title(std::move(title)),
      _url(std::move(url)),
      _mobileOnly(false)
{
    setId(_url.toString());
}

QString Hyperlink::display() const
{
    return _title;
}

QVariant Hyperlink::data(int role) const
{
    switch (role) {
    case IdRole:
        return id();
    case DisplayRole:
        return display();
    case UrlRole:
        return url();
    case MobileOnlyRole:
        return mobileOnly();
    }

    return {};
}

QJsonObject Hyperlink::asJson() const
{
    return {
        {"title", display()},
        {"url", url().toString()},
        {"html", asHtml()},
        {"mobileOnly", mobileOnly()}};
}

QString Hyperlink::asHtml(const QString &style) const
{
    if (!style.isEmpty()) {
        return "<a href=\"" + url().toString() + "\" style=\"" + style + "\">" + display() + "</a>";
    }

    return "<a href=\"" + url().toString() + "\">" + display() + "</a>";
}

} // namespace Vremenar
