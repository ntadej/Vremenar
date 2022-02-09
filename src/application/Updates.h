/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_UPDATES_H_
#define VREMENAR_UPDATES_H_

#include "common/api/APILoader.h"

#if !defined(VREMENAR_STORE) && (defined(Q_OS_MACOS) || defined(Q_OS_WINDOWS))
#include "application/SparkleHelper.h"
#endif

namespace Vremenar
{

class NetworkManager;

class Updates : public APILoader
{
    Q_OBJECT
public:
    explicit Updates(NetworkManager *network,
                     QObject *parent = nullptr);

    Q_PROPERTY(bool enabled READ enabled CONSTANT)
    Q_PROPERTY(QString server READ server NOTIFY serverChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(QString url READ url NOTIFY messageChanged)

#ifdef VREMENAR_STORE
    inline bool enabled()
    {
        return false;
    }
#else
    inline bool enabled()
    {
        return true;
    }
#endif
    inline const QString &server() { return _server; }
    inline const QString &message() { return _message; }
    inline const QString &url() { return _url; }

signals:
    void messageChanged();
    void serverChanged();
    void updateAvailable();

public slots:
    void checkVersion();
    void checkForUpdates();

private slots:
    void request();
    void response(QNetworkReply *reply) final;

private:
    void compareVersion(const QString &stable,
                        const QString &beta);

    QString _server;
    QString _message;
    QString _url;

#if !defined(VREMENAR_STORE) && (defined(Q_OS_MACOS) || defined(Q_OS_WINDOWS))
    std::unique_ptr<SparkleHelper> _sparkle{};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_UPDATES_H_
