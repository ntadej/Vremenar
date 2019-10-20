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

#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtGui/QWindow>

// Private include for the safe area margins
#ifdef Q_OS_IOS
#include <QtGui/qpa/qplatformwindow.h>
#endif

#include "qml/UIManager.h"
#include "settings/Settings.h"

namespace Vremenar
{

Qml::UIManager::UIManager(QObject *parent)
    : QObject(parent),
      _device(getDeviceType()),
      _currentWidth(Settings::DEFAULT_WIDTH),
      _currentHeight(Settings::DEFAULT_HEIGHT),
      _currentSizeRatio(static_cast<double>(_currentWidth) / static_cast<double>(_currentHeight))
{
    _currentWindow = QGuiApplication::topLevelWindows().constLast();

    primaryScreenChanged(QGuiApplication::primaryScreen());

    auto *application = qobject_cast<QGuiApplication *>(QCoreApplication::instance());
    connect(application, &QGuiApplication::primaryScreenChanged, this, &UIManager::primaryScreenChanged);
    connect(_currentWindow, &QWindow::widthChanged, this, &UIManager::windowWidthChanged);
    connect(_currentWindow, &QWindow::heightChanged, this, &UIManager::windowHeightChanged);

#ifdef Q_OS_IOS
    connect(application, &QGuiApplication::applicationStateChanged, application, [=](Qt::ApplicationState state) {
        if (state == Qt::ApplicationActive) {
            updateStatusBar();
        }
    });
#endif

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

#ifdef Q_OS_IOS
    updateStatusBar();
#endif

    Q_EMIT geometryChanged();
}

void Qml::UIManager::primaryScreenChanged(QScreen *screen)
{
    qDebug() << "Primary screen changed" << screen;

    if (_currentPrimaryScreen != nullptr) {
        disconnect(_currentPrimaryScreen, &QScreen::orientationChanged, this, &UIManager::orientationChanged);
    }

    _currentPrimaryScreen = screen;
    _currentPrimaryScreen->setOrientationUpdateMask(Qt::PortraitOrientation
                                                    | Qt::LandscapeOrientation
                                                    | Qt::InvertedPortraitOrientation
                                                    | Qt::InvertedLandscapeOrientation);

    orientationChanged(screen->orientation());

    connect(_currentPrimaryScreen, &QScreen::orientationChanged, this, &UIManager::orientationChanged);
}

void Qml::UIManager::windowWidthChanged(int width)
{
    windowSizeChanged(width, _currentHeight);
}

void Qml::UIManager::windowHeightChanged(int height)
{
    windowSizeChanged(_currentWidth, height);
}

void Qml::UIManager::windowSizeChanged(int width,
                                       int height)
{
    if (width == _currentWidth && height == _currentHeight) {
        return;
    }

    _currentWidth = width;
    _currentHeight = height;
    _currentSizeRatio = static_cast<double>(_currentWidth) / static_cast<double>(_currentHeight);

#ifdef Q_OS_IOS
    QPlatformWindow *platformWindow = _currentWindow->handle();
    if (platformWindow)
        _currentSafeAreaMargins = platformWindow->safeAreaMargins();

    Q_EMIT safetyMarginsChanged();
#endif

    Q_EMIT geometryChanged();
}

QObject *Qml::UIManager::provider(QQmlEngine *engine,
                                  QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new UIManager;
}

} // namespace Vremenar
