/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_QML_UIMANAGER_H_
#define VREMENAR_QML_UIMANAGER_H_

#include <QtCore/QMargins>
#include <QtCore/QObject>
#include <QtGui/QColor>

#include "common/Enums.h"

class QScreen;
class QJSEngine;
class QQmlEngine;
class QWindow;

namespace Vremenar
{
namespace Qml
{

class UIManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool debugging READ debugging CONSTANT)
    Q_PROPERTY(bool isMobile READ isMobile CONSTANT)
    Q_PROPERTY(Vremenar::Common::DeviceType deviceType READ getDeviceType CONSTANT)
    Q_PROPERTY(QString iconTheme READ iconTheme CONSTANT)
    Q_PROPERTY(QString iconPrefix READ iconPrefix CONSTANT)

    Q_PROPERTY(bool showButtonMapType READ showButtonMapType CONSTANT)
    Q_PROPERTY(bool showButtonMapPosition READ showButtonMapPosition NOTIFY showMapButonPositionChanged)

    Q_PROPERTY(QColor colorPrimary READ colorPrimary CONSTANT)
    Q_PROPERTY(QColor colorPrimaryDark READ colorPrimaryDark CONSTANT)

    Q_PROPERTY(QColor separatorColor READ separatorColor CONSTANT)

    Q_PROPERTY(int blurLevel READ blurLevel CONSTANT)

    Q_PROPERTY(int mapElementSize READ mapElementSize CONSTANT)
    Q_PROPERTY(int mapElementOffset READ mapElementOffset CONSTANT)

    Q_PROPERTY(int iconSizeCommon READ iconSizeCommon CONSTANT)
    Q_PROPERTY(int lineThickness READ lineThickness CONSTANT)
    Q_PROPERTY(int paddingCommon READ paddingCommon CONSTANT)
    Q_PROPERTY(int paddingHeader READ paddingHeader CONSTANT)
    Q_PROPERTY(int radiusCommon READ radiusCommon CONSTANT)

    Q_PROPERTY(int rowHeight READ rowHeight CONSTANT)
    Q_PROPERTY(QColor navBarColor READ navBarColor CONSTANT)
    Q_PROPERTY(int navBarHeight READ navBarHeight CONSTANT)

    Q_PROPERTY(int bottomSheetBaseHeight READ bottomSheetBaseHeight CONSTANT)
    Q_PROPERTY(int bottomSheetMaxWidth READ bottomSheetMaxWidth CONSTANT)

    Q_PROPERTY(int mapCoordinateChangeDuration READ mapCoordinateChangeDuration CONSTANT)
    Q_PROPERTY(int mapIconSize READ mapIconSize CONSTANT)
    Q_PROPERTY(int mapIconSizeHeight READ mapIconSizeHeight CONSTANT)
    Q_PROPERTY(int mapIconFadeDuration READ mapIconFadeDuration CONSTANT)
    Q_PROPERTY(int mapLegendSize READ mapLegendSize CONSTANT)
    Q_PROPERTY(int mapLegendSizeWide READ mapLegendSizeWide CONSTANT)
    Q_PROPERTY(int mapTimeChangeDuration READ mapTimeChangeDuration CONSTANT)
    Q_PROPERTY(int mapRefreshRotationDuration READ mapRefreshRotationDuration CONSTANT)

    Q_PROPERTY(int textCommon READ textCommon CONSTANT)
    Q_PROPERTY(int textHeader READ textHeader CONSTANT)
    Q_PROPERTY(int textSmall READ textSmall CONSTANT)
    Q_PROPERTY(QColor textColor READ textColor CONSTANT)
    Q_PROPERTY(QColor textColorPrimary READ textColorPrimary CONSTANT)
    Q_PROPERTY(QColor textColorDisabled READ textColorDisabled CONSTANT)
    Q_PROPERTY(QColor textColorSpecialLink READ textColorSpecialLink CONSTANT)

    Q_PROPERTY(QColor hoverColor READ hoverColor CONSTANT)
    Q_PROPERTY(int hoverDuration READ hoverDuration CONSTANT)

    Q_PROPERTY(int loadingDelay READ loadingDelay CONSTANT)
    Q_PROPERTY(int loadingTransitionDuration READ loadingTransitionDuration CONSTANT)

    Q_PROPERTY(int safetyMarginTop READ safetyMarginTop NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginBottom READ safetyMarginBottom NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginLeft READ safetyMarginLeft NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginRight READ safetyMarginRight NOTIFY safetyMarginsChanged)

public:
    explicit UIManager(QObject *parent = nullptr);

    [[nodiscard]] bool debugging() const;
    [[nodiscard]] bool isMobile() const;
    [[nodiscard]] QString iconTheme() const;
    [[nodiscard]] QString iconPrefix() const;

    [[nodiscard]] bool showButtonMapType() const;
    [[nodiscard]] bool showButtonMapPosition() const;

    [[nodiscard]] QColor colorPrimary() const;
    [[nodiscard]] QColor colorPrimaryLight() const;
    [[nodiscard]] QColor colorPrimaryDark() const;

    [[nodiscard]] QColor separatorColor() const;

    [[nodiscard]] int blurLevel() const;

    [[nodiscard]] int mapElementSize() const;
    [[nodiscard]] int mapElementOffset() const;

    [[nodiscard]] int iconSizeCommon() const;
    [[nodiscard]] int lineThickness() const;
    [[nodiscard]] int paddingCommon() const;
    [[nodiscard]] int paddingHeader() const;
    [[nodiscard]] int radiusCommon() const;

    [[nodiscard]] int rowHeight() const;
    [[nodiscard]] QColor navBarColor() const;
    [[nodiscard]] int navBarHeight() const;

    [[nodiscard]] int bottomSheetBaseHeight() const;
    [[nodiscard]] int bottomSheetMaxWidth() const;

    [[nodiscard]] int mapCoordinateChangeDuration() const;
    [[nodiscard]] int mapIconSize() const;
    [[nodiscard]] int mapIconSizeHeight() const;
    [[nodiscard]] int mapIconFadeDuration() const;
    [[nodiscard]] int mapLegendSize() const;
    [[nodiscard]] int mapLegendSizeWide() const;
    [[nodiscard]] int mapTimeChangeDuration() const;
    [[nodiscard]] int mapRefreshRotationDuration() const;

    [[nodiscard]] int textCommon() const;
    [[nodiscard]] int textHeader() const;
    [[nodiscard]] int textSmall() const;
    [[nodiscard]] QColor textColor() const;
    [[nodiscard]] QColor textColorPrimary() const;
    [[nodiscard]] QColor textColorDisabled() const;
    [[nodiscard]] QColor textColorSpecialLink() const;

    [[nodiscard]] QColor hoverColor() const;
    [[nodiscard]] int hoverDuration() const;

    [[nodiscard]] int loadingDelay() const;
    [[nodiscard]] int loadingTransitionDuration() const;

    [[nodiscard]] inline int safetyMarginTop() const { return _currentSafeAreaMargins.top(); }
    [[nodiscard]] inline int safetyMarginBottom() const { return _currentSafeAreaMargins.bottom(); }
    [[nodiscard]] inline int safetyMarginLeft() const { return _currentSafeAreaMargins.left(); }
    [[nodiscard]] inline int safetyMarginRight() const { return _currentSafeAreaMargins.right(); }

    Q_INVOKABLE void debugAction();

    static QObject *provider(QQmlEngine *engine,
                             QJSEngine *scriptEngine);

Q_SIGNALS:
    void geometryChanged();
    void safetyMarginsChanged();

    void showMapButonPositionChanged();

private Q_SLOTS:
    void orientationChanged(Qt::ScreenOrientation orientation);
    void primaryScreenChanged(QScreen *screen);
    void windowWidthChanged(int width);
    void windowHeightChanged(int height);
    void windowSizeChanged(int width,
                           int height);
    void updateSafeAreaMargins();

private:
    static Common::DeviceType getDeviceType();
#ifdef Q_OS_IOS
    static Common::DeviceType getDeviceTypeIOS();
#endif
#ifdef Q_OS_ANDROID
    static Common::DeviceType getDeviceTypeAndroid();
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    QMargins safeAreaMargins();
#endif

    const Common::DeviceType _device;

    QScreen *_currentPrimaryScreen{}; // owned by Qt
    Qt::ScreenOrientation _currentOrientation = Qt::PrimaryOrientation;
    QWindow *_currentWindow{}; // owned by Qt

    int _currentWidth;
    int _currentHeight;
    double _currentSizeRatio;
    QMargins _currentSafeAreaMargins{0, 0, 0, 0};
};

} // namespace Qml
} // namespace Vremenar

#endif // VREMENAR_QML_UIMANAGER_H_
