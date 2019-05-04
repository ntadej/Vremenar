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
    Q_PROPERTY(QColor colorPrimary READ colorPrimary CONSTANT)
    Q_PROPERTY(QColor colorPrimaryLight READ colorPrimaryLight CONSTANT)
    Q_PROPERTY(QColor colorPrimaryDark READ colorPrimaryDark CONSTANT)

    Q_PROPERTY(QColor separatorColor READ separatorColor CONSTANT)

    Q_PROPERTY(int blurLevel READ blurLevel CONSTANT)

    Q_PROPERTY(int buttonMapSize READ buttonMapSize CONSTANT)

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

    Q_PROPERTY(int textCommon READ textCommon CONSTANT)
    Q_PROPERTY(int textHeader READ textHeader CONSTANT)
    Q_PROPERTY(QColor textColor READ textColor CONSTANT)
    Q_PROPERTY(QColor textColorPrimary READ textColorPrimary CONSTANT)

    Q_PROPERTY(QColor hoverColor READ hoverColor CONSTANT)
    Q_PROPERTY(int hoverDuration READ hoverDuration CONSTANT)

    Q_PROPERTY(int safetyMarginTop READ safetyMarginTop NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginBottom READ safetyMarginBottom NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginLeft READ safetyMarginLeft NOTIFY safetyMarginsChanged)
    Q_PROPERTY(int safetyMarginRight READ safetyMarginRight NOTIFY safetyMarginsChanged)

public:
    explicit UIManager(QObject *parent = nullptr);

    QColor colorPrimary() const;
    QColor colorPrimaryLight() const;
    QColor colorPrimaryDark() const;

    QColor separatorColor() const;

    int blurLevel() const;

    int buttonMapSize() const;

    int iconSizeCommon() const;
    int lineThickness() const;
    int paddingCommon() const;
    int paddingHeader() const;
    int radiusCommon() const;

    int rowHeight() const;
    QColor navBarColor() const;
    int navBarHeight() const;

    int bottomSheetBaseHeight() const;
    int bottomSheetMaxWidth() const;

    int textCommon() const;
    int textHeader() const;
    QColor textColor() const;
    QColor textColorPrimary() const;

    QColor hoverColor() const;
    int hoverDuration() const;

    inline int safetyMarginTop() const { return _currentSafeAreaMargins.top(); }
    inline int safetyMarginBottom() const { return _currentSafeAreaMargins.bottom(); }
    inline int safetyMarginLeft() const { return _currentSafeAreaMargins.left(); }
    inline int safetyMarginRight() const { return _currentSafeAreaMargins.right(); }

    static QObject *provider(QQmlEngine *engine,
                             QJSEngine *scriptEngine);

signals:
    void geometryChanged();
    void safetyMarginsChanged();

private slots:
    void orientationChanged(Qt::ScreenOrientation orientation);
    void primaryScreenChanged(QScreen *screen);
    void windowWidthChanged(int width);
    void windowHeightChanged(int height);
    void windowSizeChanged(int width,
                           int height);

private:
    static Common::DeviceType getDeviceType();
#ifdef Q_OS_IOS
    static Common::DeviceType getDeviceTypeIOS();

    void updateStatusBar();
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
