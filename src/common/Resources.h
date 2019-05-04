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

#ifndef VREMENAR_RESOURCES_H_
#define VREMENAR_RESOURCES_H_

#include <QtCore/QString>

namespace Vremenar
{
namespace Resources
{

// Resources locators
QString path(const QString &file);
QString resource(const QString &file);

// Special locations
QString appData();
QString logLocation();

} // namespace Resources
} // namespace Vremenar

#endif // VREMENAR_RESOURCES_H_
