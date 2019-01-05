/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LOCALSERVER_H_
#define VREMENAR_LOCALSERVER_H_

#include <QtNetwork/QLocalServer>

namespace Vremenar
{

class LocalServer : public QObject
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);
    ~LocalServer() = default;

signals:
    void connected();

private slots:
    void newConnection();

private:
    std::unique_ptr<QLocalServer> _server;
};

} // namespace Vremenar

#endif // VREMENAR_LOCALSERVER_H_
