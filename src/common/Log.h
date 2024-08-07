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

#ifndef VREMENAR_LOG_H_
#define VREMENAR_LOG_H_

#include <QtCore/QString>

namespace Vremenar::Log
{

void output(QtMsgType type,
            const QMessageLogContext &context,
            const QString &msg);

void setup();

} // namespace Vremenar::Log

#endif // VREMENAR_LOG_H_
