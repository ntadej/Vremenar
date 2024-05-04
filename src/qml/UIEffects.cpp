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

#include "common/Enums.h"

namespace Vremenar
{

int Qml::UIManager::blurLevel() const { return 64; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::shadowRadius() const
{
    if (_theme == Common::LightTheme) {
        return 9; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return 12; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

int Qml::UIManager::mapCoordinateChangeDuration() const { return 1000; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapIconFadeDuration() const { return 100; }          // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapTimeChangeDuration() const { return 100; }        // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::mapRefreshRotationDuration() const { return 1000; }  // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::hoverDuration() const { return 200; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

int Qml::UIManager::loadingDelay() const { return 250; }             // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
int Qml::UIManager::loadingTransitionDuration() const { return 50; } // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace Vremenar
