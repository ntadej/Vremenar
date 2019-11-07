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

int Qml::UIManager::blurLevel() const { return 64; }

int Qml::UIManager::mapIconFadeDuration() const { return 100; }
int Qml::UIManager::mapTimeChangeDuration() const { return 100; }
int Qml::UIManager::mapRefreshRotationDuration() const { return 1000; }

int Qml::UIManager::hoverDuration() const { return 200; }

int Qml::UIManager::loadingDelay() const { return 250; }
int Qml::UIManager::loadingTransitionDuration() const { return 50; }

} // namespace Vremenar
