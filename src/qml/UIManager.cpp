/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
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

    qDebug() << "Running on device type" << _device;
}

bool Qml::UIManager::debugging() const
{
#if defined(Q_OS_MACOS) && defined(QT_DEBUG)
    return !mapOnly();
#else
    return false;
#endif
}

bool Qml::UIManager::isMobile() const
{
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    return true;
#else
    return false;
#endif
}

bool Qml::UIManager::isTV() const
{
    return _device == Common::AndroidTV || _device == Common::FireTV;
}

bool Qml::UIManager::mapOnly() const
{
    return false;
}

Common::Theme Qml::UIManager::theme() const
{
    return _theme;
}

void Qml::UIManager::setTheme(Common::Theme theme)
{
    if (_theme != theme) {
        _theme = theme;
        Q_EMIT themeChanged();
    }
}

QString Qml::UIManager::iconTheme() const
{
    return QStringLiteral("Ionicons");
}

QString Qml::UIManager::iconPrefix() const
{
#if defined(Q_OS_ANDROID)
    return QStringLiteral("md-");
#else
    return QStringLiteral("ios-");
#endif
}

Common::DeviceType Qml::UIManager::getDeviceType()
{
#if defined(Q_OS_MACOS) && defined(QT_DEBUG)
    return Common::DebuggingDevice;
#elif defined(Q_OS_MACOS)
    return Common::Desktop;
#elif defined(Q_OS_IOS)
    return getDeviceTypeIOS();
#elif defined(Q_OS_ANDROID)
    return getDeviceTypeAndroid();
#elif defined(Q_OS_LINUX)
    return Common::Desktop;
#elif defined(Q_OS_WIN)
    return Common::Desktop;
#else
    return Common::UnknownDevice;
#endif
}

void Qml::UIManager::orientationChanged(Qt::ScreenOrientation orientation)
{
    qDebug() << "Orientation changed" << orientation;

    _currentOrientation = orientation;

    updateSafeAreaMargins();

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

    updateSafeAreaMargins();

    Q_EMIT geometryChanged();
}

void Qml::UIManager::updateSafeAreaMargins()
{
#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    _currentSafeAreaMargins = safeAreaMargins();
    Q_EMIT safetyMarginsChanged();
#endif

#ifdef Q_OS_MACOS
    if (_device == Common::DebuggingDevice) {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        _currentSafeAreaMargins = QMargins(40, 25, 25, 25);
        Q_EMIT safetyMarginsChanged();
    }
#endif
}

void Qml::UIManager::toast(const QString &message)
{
    qDebug() << message;
#ifdef Q_OS_ANDROID
    toastAndroid(message);
#endif
}

void Qml::UIManager::debugAction(int key)
{
    auto keyEnum(static_cast<Qt::Key>(key));

    qDebug() << keyEnum;
}

bool Qml::UIManager::showButtonMapType() const
{
#if defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    return false;
#else
    return _device != Common::AndroidTV && _device != Common::FireTV;
#endif
}

bool Qml::UIManager::showButtonMapPosition() const
{
    return _device != Common::AndroidTV && _device != Common::FireTV;
}

QObject *Qml::UIManager::provider(QQmlEngine *engine,
                                  QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new UIManager;
}

} // namespace Vremenar
