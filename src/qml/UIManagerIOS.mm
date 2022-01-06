/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtGui/QWindow>

// Private include for the safe area margins
#include <QtGui/qpa/qplatformwindow.h>

#include <UIKit/UIDevice.h>

#include "qml/UIManager.h"

namespace Vremenar
{

Common::DeviceType Qml::UIManager::getDeviceTypeIOS()
{
    UIUserInterfaceIdiom idiom = [UIDevice currentDevice].userInterfaceIdiom;
    if (idiom == UIUserInterfaceIdiomPad) {
        return Common::iPad;
    }
    if (idiom == UIUserInterfaceIdiomPhone) {
        return Common::iPhone;
    }

    return Common::UnknownDevice;
}

QMargins Qml::UIManager::safeAreaMargins()
{
    QPlatformWindow *platformWindow = _currentWindow->handle();
    if (platformWindow != nullptr) {
        return platformWindow->safeAreaMargins();
    }

    return QMargins();
}

bool Qml::UIManager::hasSFIcons()
{
    if (@available(iOS 13.0, *)) {
        return true;
    } else {
        return false;
    }
}

} // namespace Vremenar
