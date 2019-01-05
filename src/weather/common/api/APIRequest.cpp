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

#include "weather/common/api/APIRequest.h"

namespace Vremenar
{

APIRequest::APIRequest()
    : QNetworkRequest(),
      _operation(QNetworkAccessManager::GetOperation)
{
    setRawHeader("Content-type", "application/json");
}

void APIRequest::setBaseUrl(const QString &url)
{
    _baseUrl = url;
}

void APIRequest::setCall(const QString &call)
{
    _call = call;
}

void APIRequest::setUrl(const QString &url)
{
    QNetworkRequest::setUrl(QUrl(_baseUrl + url));
}

void APIRequest::setOperation(const QNetworkAccessManager::Operation &operation)
{
    _operation = operation;
}

void APIRequest::setExtra(const QVariant &extra)
{
    _extra = extra;
}

QByteArray APIRequest::data() const
{
    return QJsonDocument(_data).toJson();
}

void APIRequest::setData(const QJsonObject &data)
{
    _data = data;
}

} // namespace Vremenar
