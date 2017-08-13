/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_MOBILEAPPLICATION_H_
#define VREMENAR_MOBILEAPPLICATION_H_

#include <QtGui/QGuiApplication>

class QWindow;

class MobileApplication : public QGuiApplication
{
    Q_OBJECT
public:
    explicit MobileApplication(int &argc,
                               char **argv);
    ~MobileApplication();

    static void preInit();
    void postInit();
};

#endif // VREMENAR_MOBILEAPPLICATION_H_
