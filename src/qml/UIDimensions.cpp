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

int Qml::UIManager::buttonMapSize() const { return 44; }

int Qml::UIManager::iconSizeCommon() const { return 32; }
int Qml::UIManager::lineThickness() const { return 1; }
int Qml::UIManager::paddingCommon() const { return 15; }
int Qml::UIManager::paddingHeader() const { return 5; }
int Qml::UIManager::radiusCommon() const { return 10; }

int Qml::UIManager::rowHeight() const { return 44; }
int Qml::UIManager::navBarHeight() const { return 44; }

int Qml::UIManager::bottomSheetBaseHeight() const { return 66; }
int Qml::UIManager::bottomSheetMaxWidth() const { return 640; }

} // namespace Vremenar
