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

#include "qml/UIManager.h"

namespace Vremenar
{

int Qml::UIManager::mapElementSize() const { return 44; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapElementOffset() const { return 8; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapSliderSize() const { return 24; }   // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::iconSizeCommon() const
{
#if defined(Q_OS_WINDOWS)
    return 28; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#elif defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    return 14; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#else
    return 32; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
}
int Qml::UIManager::iconSizeLarge() const { return 48; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::iconSizePrevNext() const
{
#if defined(Q_OS_WINDOWS)
    return 22; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#else
    return iconSizeCommon();
#endif
}
int Qml::UIManager::iconSizeFirstLast() const
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    return iconSizeCommon();
#elif defined(Q_OS_WINDOWS)
    return 24; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#else
    return 26; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
}
int Qml::UIManager::iconSizeCheckMark() const
{
#if defined(Q_OS_MACOS) || defined(Q_OS_IOS)
    return 8; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#else
    return iconSizeCommon();
#endif
}
int Qml::UIManager::iconAlertArea() const { return 36; }      // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::iconBorderThickness() const { return 3; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::lineThickness() const { return 1; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::paddingCommon() const { return 15; }      // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::paddingSmall() const { return 8; }        // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::paddingHeader() const { return 5; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::radiusCommon() const { return 10; }       // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::rowHeight() const { return 44; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::navBarHeight() const
{
#if !defined(Q_OS_ANDROID) && defined(Q_OS_LINUX)
    return 0;
#else
    return 44; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
#endif
}

int Qml::UIManager::bottomSheetBaseHeight() const { return 44; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::bottomSheetMaxWidth() const { return 680; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::smallWidthThreshold() const { return 320; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::mapIconSize() const { return 48; }            // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapIconSizeHeight() const { return 38; }      // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapLegendSize() const { return 20; }          // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapLegendSizeTextBased() const { return 50; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::windowButtonWidth() const { return 45; }    // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::windowButtonHeight() const { return 28; }   // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::windowButtonIconSize() const { return 10; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace Vremenar
