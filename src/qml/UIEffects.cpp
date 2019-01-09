/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "qml/UIManager.h"

namespace Vremenar
{

int Qml::UIManager::blurLevel() const { return 64; }

int Qml::UIManager::hoverDuration() const { return 200; }

} // namespace Vremenar
