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

#ifndef VREMENAR_APIHELPERS_H_
#define VREMENAR_APIHELPERS_H_

#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace Vremenar
{
namespace API
{

QString generateParameters(const QVariantMap &map);

} // namespace API
} // namespace Vremenar

#endif // VREMENAR_API_HELPERS_H_
