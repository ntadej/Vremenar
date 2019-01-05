/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>

#include "common/api/APIRequestBase.h"

namespace Vremenar
{

APIRequestBase::APIRequestBase()
    : QNetworkRequest(),
      _operation(QNetworkAccessManager::GetOperation)
{
    setRawHeader("Content-type", "application/json");
}

void APIRequestBase::setBaseUrl(const QString &url)
{
    _baseUrl = url;
}

void APIRequestBase::setCall(const QString &call)
{
    _call = call;
}

void APIRequestBase::setUrl(const QString &url)
{
    QNetworkRequest::setUrl(QUrl(_baseUrl + url));
}

void APIRequestBase::setOperation(const QNetworkAccessManager::Operation &operation)
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
