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

#ifndef VREMENAR_MOBILEAPPLICATION_H_
#define VREMENAR_MOBILEAPPLICATION_H_

#include <QtCore/QObject>
#include <QtGui/QGuiApplication>

namespace Vremenar
{

class MobileApplication : public QGuiApplication
{
    Q_OBJECT
public:
    static MobileApplication init(int &argc, // NOLINT(google-runtime-references)
                                  char **argv);

private:
    explicit MobileApplication(int &argc,
                               char **argv,
                               QObject *parent = nullptr);
};

} // namespace Vremenar

#endif // VREMENAR_MOBILEAPPLICATION_H_
