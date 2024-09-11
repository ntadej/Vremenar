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

#ifndef VREMENAR_APISOURCES_H_
#define VREMENAR_APISOURCES_H_

#include <QtCore/QUrlQuery>

namespace Vremenar::API
{

QUrlQuery sourceQuery();
QUrlQuery sourceAndLocaleQuery();

} // namespace Vremenar::API

#endif // VREMENAR_APISOURCES_H_
