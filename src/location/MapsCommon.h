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

#ifndef VREMENAR_MAPSCOMMON_H_
#define VREMENAR_MAPSCOMMON_H_

#include <memory>

#include <QtCore/QString>

#include "common/containers/Hyperlink.h"

namespace Vremenar
{
namespace Maps
{

QString style();
std::vector<std::unique_ptr<Hyperlink>> copyright();

} // namespace Maps
} // namespace Vremenar

#endif // VREMENAR_MAPSCOMMON_H_
