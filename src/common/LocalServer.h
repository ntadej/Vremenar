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

#ifndef VREMENAR_LOCALSERVER_H_
#define VREMENAR_LOCALSERVER_H_

#include <QtCore/QObject>
#include <QtNetwork/QLocalServer>

#include <memory>

namespace Vremenar
{

class LocalServer : public QObject
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);

signals:
    void connected();

private slots:
    void newConnection();

private:
    std::unique_ptr<QLocalServer> _server;
};

} // namespace Vremenar

#endif // VREMENAR_LOCALSERVER_H_
