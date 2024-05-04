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

#ifndef VREMENAR_OUTPUT_H_
#define VREMENAR_OUTPUT_H_

#include <QtCore/QString>
#include <QtCore/QTextStream>

namespace Vremenar
{

class Output : public QTextStream
{
public:
    explicit Output(bool error = false);

    Output &operator<<(const QString &string);

    static void welcome();

    static void help();

    static void errorGeneric();
    static void errorMissing(const QString &arg);
    static void errorUnknown(const QString &arg);
};

} // namespace Vremenar

#endif // VREMENAR_OUTPUT_H_
