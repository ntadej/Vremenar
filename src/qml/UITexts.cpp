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

#include "qml/UIManager.h"

namespace Vremenar
{

int Qml::UIManager::textCommon() const { return 17; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::textHeader() const { return 13; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::textSmall() const { return 12; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace Vremenar
