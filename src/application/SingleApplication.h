/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_SINGLEAPPLICATION_H_
#define VREMENAR_SINGLEAPPLICATION_H_

#include <QtWidgets/QApplication>

#ifndef Q_OS_MACOS
class LocalServer;
#endif

class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    explicit SingleApplication(int &argc,
                               char **argv);
    ~SingleApplication();

    bool shouldContinue();

signals:
    void activate();

private:
#ifndef Q_OS_MACOS
    LocalServer *_server;
#endif
    bool _shouldContinue;
};

#endif // VREMENAR_SINGLEAPPLICATION_H_
