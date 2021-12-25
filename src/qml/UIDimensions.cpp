/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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

int Qml::UIManager::mapElementSize() const { return 44; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapElementOffset() const { return 8; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::iconSizeCommon() const { return 32; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::iconSizeLarge() const { return 48; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::iconSizeSpecialControl() const
{
#if defined(Q_OS_ANDROID)
    return 24; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#else
    return 26; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
}
int Qml::UIManager::iconBorderThickness() const { return 3; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::lineThickness() const { return 1; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::paddingCommon() const { return 15; }      // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::paddingHeader() const { return 5; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::radiusCommon() const { return 10; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::rowHeight() const { return 44; }    // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::navBarHeight() const
{
#if !defined(Q_OS_ANDROID) && (defined(Q_OS_WINDOWS) || defined(Q_OS_LINUX))
    return 0;
#else
    return 44; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
}

int Qml::UIManager::bottomSheetBaseHeight() const { return 44; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::bottomSheetMaxWidth() const { return 680; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::mapIconSize() const { return 48; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapIconSizeHeight() const { return 38; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapLegendSize() const { return 20; }     // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapLegendSizeTextBased() const { return 50; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace Vremenar
