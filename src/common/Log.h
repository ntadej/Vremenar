/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LOG_H_
#define VREMENAR_LOG_H_

#include <QtCore/QtGlobal>

namespace Vremenar
{
    namespace Log
    {
        void output(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &msg);

        void setup();
    }
}

#endif // VREMENAR_LOG_H_
