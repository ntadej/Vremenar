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

#include <QtGui/QColor>

namespace Vremenar
{

QColor Qml::UIManager::colorPrimary() const
{
    if (_theme == Common::LightTheme) {
        return {50, 165, 115}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 219, 79}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}
QColor Qml::UIManager::colorPrimaryDark() const
{
    if (_theme == Common::LightTheme) {
        return {40, 130, 110}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 181, 36}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::separatorColor() const
{
    if (_theme == Common::LightTheme) {
        return {188, 187, 193}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {74, 74, 78}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::shadowColor() const
{
    if (_theme == Common::LightTheme) {
        return {124, 124, 128}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {27, 27, 27}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::navBarColor() const
{
    if (_theme == Common::LightTheme) {
        return {249, 249, 249, 100}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {27, 27, 27, 160}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::alertMinorColor() const
{
    if (_theme == Common::LightTheme) {
        return {254, 217, 35}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {254, 217, 35}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::alertModerateColor() const
{
    if (_theme == Common::LightTheme) {
        return {253, 148, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {254, 148, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::alertSevereColor() const
{
    if (_theme == Common::LightTheme) {
        return {254, 0, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {254, 0, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::alertExtremeColor() const
{
    if (_theme == Common::LightTheme) {
        return {174, 15, 67}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {174, 15, 67}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColor() const
{
    if (_theme == Common::LightTheme) {
        return {0, 0, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 255, 255}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColorInverted() const
{
    if (_theme == Common::LightTheme) {
        return {255, 255, 255}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {0, 0, 0}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColorInactive() const
{
    if (_theme == Common::LightTheme) {
        return {80, 80, 80}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {200, 200, 200}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColorPrimary() const
{
    if (_theme == Common::LightTheme) {
        return colorPrimary(); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return colorPrimary();
}

QColor Qml::UIManager::textColorSpecialLink() const
{
    if (_theme == Common::LightTheme) {
        return {80, 80, 80}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {200, 200, 200}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColorMap() const
{
    if (_theme == Common::LightTheme) {
        return {40, 40, 40}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 255, 255}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::textColorMapSecondary() const
{
    if (_theme == Common::LightTheme) {
        return {80, 80, 80}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {200, 200, 200}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::buttonColor() const
{
    if (_theme == Common::LightTheme) {
        return colorPrimary();
    }
    return textColor();
}

QColor Qml::UIManager::buttonColorHover() const
{
    if (_theme == Common::LightTheme) {
        return colorPrimaryDark();
    }
    return colorPrimary();
}

QColor Qml::UIManager::buttonColorDisabled() const
{
    if (_theme == Common::LightTheme) {
        return {149, 149, 149}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {200, 200, 200}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::hoverColor() const
{
    if (_theme == Common::LightTheme) {
        return {0, 0, 0, 16}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 255, 255, 16}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::windowButtonHoverColor() const
{
    if (_theme == Common::LightTheme) {
        return {0, 0, 0, 32}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 255, 255, 32}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::windowButtonDownColor() const
{
    if (_theme == Common::LightTheme) {
        return {0, 0, 0, 16}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    }
    return {255, 255, 255, 16}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

QColor Qml::UIManager::windowButtonSpecialColor() const
{
    return {196, 42, 28, 254}; // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

} // namespace Vremenar
