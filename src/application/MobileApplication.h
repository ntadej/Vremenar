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

#ifndef VREMENAR_MOBILEAPPLICATION_H_
#define VREMENAR_MOBILEAPPLICATION_H_

#include <QtGui/QGuiApplication>

namespace Vremenar
{

class MobileApplication : public QGuiApplication
{
    Q_OBJECT
public:
    explicit MobileApplication(int &argc,
                               char **argv,
                               QObject *parent = nullptr);

    void postInit() const;

#ifdef Q_OS_IOS
    static bool supportsSFSymbols();
#endif
};

} // namespace Vremenar

#endif // VREMENAR_MOBILEAPPLICATION_H_
