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

#ifndef VREMENAR_SPARKLEHELPER_H_
#define VREMENAR_SPARKLEHELPER_H_

#include <QtCore/QObject>

#ifdef VREMENAR_OBJC
#include <Sparkle/Sparkle.h>
#endif

namespace Vremenar
{

class SparkleHelper
{
    Q_DISABLE_COPY_MOVE(SparkleHelper)
public:
    explicit SparkleHelper();
#if defined(Q_OS_WINDOWS)
    ~SparkleHelper();
#else
    ~SparkleHelper() = default;
#endif

    void checkForUpdates();

private:
#ifdef VREMENAR_OBJC
    SPUStandardUpdaterController *updaterController;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_SPARKLEHELPER_H_
