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

#ifndef VREMENAR_APIREQUESTBASE_H_
#define VREMENAR_APIREQUESTBASE_H_

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

namespace Vremenar
{

class APIRequestBase : public QNetworkRequest
{
public:
    APIRequestBase();

    inline const QString &call() const { return _call; }
    inline QNetworkAccessManager::Operation operation() const { return _operation; }
    inline const QVariant &extra() const { return _extra; }
    QByteArray data() const;

    void setBaseUrl(const QString &url);
    void setCall(const QString &call);
    void setUrl(const QString &url);
    void setOperation(QNetworkAccessManager::Operation operation);
    void setExtra(const QVariant &extra);
    void setData(const QJsonObject &data);

private:
    QString _baseUrl;
    QString _call;
    QNetworkAccessManager::Operation _operation{QNetworkAccessManager::GetOperation};
    QVariant _extra;
    QJsonObject _data;
};

} // namespace Vremenar

#endif // VREMENAR_APIREQUESTBASE_H_
