/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>

#include "qml/UIManager.h"
#include "settings/Settings.h"

namespace Vremenar
{

Qml::UIManager::UIManager()
    : _device(getDeviceType()),
      _currentWidth(Settings::DEFAULT_WIDTH),
      _currentHeight(Settings::DEFAULT_HEIGHT)
{
    auto *application = qobject_cast<QGuiApplication *>(QCoreApplication::instance());
    primaryScreenChanged(application->primaryScreen());

    connect(application, &QGuiApplication::primaryScreenChanged, this, &UIManager::primaryScreenChanged);

    qDebug() << "Running on device type" << _device;
}

Common::DeviceType Qml::UIManager::getDeviceType()
{
#if defined(Q_OS_MACOS)
    return Common::Desktop;
#elif defined(Q_OS_IOS)
    return getDeviceTypeIOS();
#else
    return Common::UnknownDevice;
#endif
}

void Qml::UIManager::orientationChanged(Qt::ScreenOrientation orientation)
{
    qDebug() << "Orientation changed" << orientation;

    _currentOrientation = orientation;
}

void Qml::UIManager::primaryScreenChanged(QScreen *screen)
{
    qDebug() << "Primary screen changed" << screen;

    if (_currentPrimaryScreen) {
        disconnect(_currentPrimaryScreen, &QScreen::orientationChanged, this, &UIManager::orientationChanged);
    }

    _currentPrimaryScreen = screen;
    _currentPrimaryScreen->setOrientationUpdateMask(Qt::PortraitOrientation
                                                    | Qt::LandscapeOrientation
                                                    | Qt::InvertedPortraitOrientation
                                                    | Qt::InvertedLandscapeOrientation);

    _currentOrientation = screen->orientation();

    connect(_currentPrimaryScreen, &QScreen::orientationChanged, this, &UIManager::orientationChanged);
}

void Qml::UIManager::primaryWindowSizeChanged(qreal width,
                                              qreal height)
{
    qDebug() << "Primary window size changed" << width << height << width / height;

    _currentWidth = width;
    _currentHeight = height;
}

QObject *Qml::UIManager::provider(QQmlEngine *engine,
                                  QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new UIManager;
}

} // namespace Vremenar
