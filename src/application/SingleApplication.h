/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_SINGLEAPPLICATION_H_
#define VREMENAR_SINGLEAPPLICATION_H_

#include <memory>

#include <QtWidgets/QApplication>

#ifndef Q_OS_MACOS
#include "common/LocalServer.h"
#endif

namespace Vremenar
{

class SingleApplication : public QApplication
{
    Q_OBJECT
public:
    explicit SingleApplication(int &argc, // NOLINT(google-runtime-references)
                               char **argv,
                               QObject *parent = nullptr);

    [[nodiscard]] static bool shouldContinue();

signals:
    void activate();

private:
#ifndef Q_OS_MACOS
    std::unique_ptr<LocalServer> _server;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_SINGLEAPPLICATION_H_
