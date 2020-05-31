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

#ifndef VREMENAR_UPDATES_H_
#define VREMENAR_UPDATES_H_

#include "common/api/APILoader.h"

#ifdef Q_OS_MACOS
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

    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(QString url READ url NOTIFY messageChanged)

    inline const QString &message() { return _message; }
    inline const QString &url() { return _url; }

Q_SIGNALS:
    void messageChanged();
    void updateAvailable();

public Q_SLOTS:
    void checkForUpdates();

private Q_SLOTS:
    void request();
    void response(QNetworkReply *reply) final;

private:
    void compareVersion(const QString &stable,
                        const QString &beta);

    QString _message;
    QString _url;

#ifdef Q_OS_MACOS
    std::unique_ptr<SparkleHelper> _sparkle{};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_UPDATES_H_
