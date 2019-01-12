/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtGui/QWindow>

#include <UIKit/UIDevice.h>
#include <UIKit/UIViewController.h>

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

void Qml::UIManager::updateStatusBar()
{
    if (_device == Common::iPhone
        && (_currentOrientation == Qt::LandscapeOrientation || _currentOrientation == Qt::InvertedLandscapeOrientation)) {
        _currentWindow->setWindowStates(_currentWindow->windowStates() | Qt::WindowFullScreen);
    } else {
        _currentWindow->setWindowStates(_currentWindow->windowStates() & (~Qt::WindowFullScreen));
    }
}

}

@interface QIOSViewController : UIViewController
@end

@interface QIOSViewController (VremenarView)
@end

@implementation QIOSViewController (VremenarView)

- (UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}

@end
