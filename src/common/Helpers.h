/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_HELPERS_H_
#define VREMENAR_HELPERS_H_

#include <QtCore/QLatin1String>

// Helper class
class CString : public QLatin1String
{
public:
    constexpr CString(const char *const s)
        : QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

#endif // VREMENAR_HELPERS_H_
