/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_APIREQUEST_H_
#define VREMENAR_APIREQUEST_H_

#include <QtCore/QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

class APIRequest : public QNetworkRequest
{
public:
    APIRequest();
    virtual ~APIRequest();

    inline QString call() const { return _call; }
    inline QNetworkAccessManager::Operation operation() const { return _operation; }
    inline QVariant extra() const { return _extra; }
    QByteArray data() const;

    void setBaseUrl(const QString &url);
    void setCall(const QString &call);
    void setUrl(const QString &url);
    void setOperation(const QNetworkAccessManager::Operation &operation);
    void setExtra(const QVariant &extra);
    void setData(const QJsonObject &data);

private:
    QString _baseUrl;
    QString _call;
    QNetworkAccessManager::Operation _operation;
    QVariant _extra;
    QJsonObject _data;
};

#endif // VREMENAR_APIREQUEST_H_
