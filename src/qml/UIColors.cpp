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

QColor Qml::UIManager::colorPrimary() const { return {62, 150, 243}; }
QColor Qml::UIManager::colorPrimaryLight() const { return {90, 200, 251}; }
QColor Qml::UIManager::colorPrimaryDark() const { return {49, 105, 218}; }

QColor Qml::UIManager::separatorColor() const { return {50, 50, 51}; }

QColor Qml::UIManager::navBarColor() const { return {27, 27, 27, 160}; }

QColor Qml::UIManager::textColor() const { return {255, 255, 255}; }
QColor Qml::UIManager::textColorPrimary() const { return colorPrimary(); }

QColor Qml::UIManager::hoverColor() const { return {255, 255, 255, 16}; }

} // namespace Vremenar
