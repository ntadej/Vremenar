/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <UIKit/UIDevice.h>

#include "qml/UIManager.h"

namespace Vremenar
{

Common::DeviceType Qml::UIManager::getDeviceTypeIOS()
{
    UIUserInterfaceIdiom idiom = [UIDevice currentDevice].userInterfaceIdiom;
    if (idiom == UIUserInterfaceIdiomPad)
        return Common::iPad;
    else if (idiom == UIUserInterfaceIdiomPhone)
        return Common::iPhone;
    else
        return Common::UnknownDevice;
}

}
