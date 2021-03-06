/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_BASEAPPLICATION_H_
#define VREMENAR_BASEAPPLICATION_H_

namespace Vremenar
{
namespace Application
{

constexpr int RESTART_CODE{1111};

void preInit();

} // namespace Application
} // namespace Vremenar

#endif // VREMENAR_BASEAPPLICATION_H_
