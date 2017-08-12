/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_COMMON_H_
#define VREMENAR_COMMON_H_

#include <QtCore/QString>

namespace Vremenar
{
    // Vremenar name and executable
    QString name();
    QString executable();
    QString domain();
    QString localServer();

    // Version
    QString version();
    int build();
}

#endif // VREMENAR_COMMON_H_
