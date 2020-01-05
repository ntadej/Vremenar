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

#include <QtCore/QJsonDocument>
#include <QtCore/QSysInfo>

#include "common/api/APIRequestBase.h"

#include "Config.h"

namespace Vremenar
{

APIRequestBase::APIRequestBase()
{
    static const QByteArray agent = QStringLiteral("%1/%2 (%3)").arg(Vremenar::name).arg(Vremenar::version).arg(QSysInfo::prettyProductName()).toLatin1();

    setRawHeader("Content-type", "application/json");
    setRawHeader("User-Agent", agent);
}

void APIRequestBase::setBaseUrl(const QString &url)
{
    _baseUrl = url;
}

void APIRequestBase::setCall(const QString &call)
{
    _call = call;
}

void APIRequestBase::setUrl(const QString &url,
                            const QUrlQuery &query)
{
    QUrl u(_baseUrl + url);
    if (!query.isEmpty()) {
        u.setQuery(query);
    }
    QNetworkRequest::setUrl(u);
}

void APIRequestBase::setOperation(QNetworkAccessManager::Operation operation)
{
    _operation = operation;
}

void APIRequestBase::setExtra(const QVariant &extra)
{
    _extra = extra;
}

QByteArray APIRequestBase::data() const
{
    return QJsonDocument(_data).toJson();
}

void APIRequestBase::setData(const QJsonObject &data)
{
    _data = data;
}

} // namespace Vremenar
