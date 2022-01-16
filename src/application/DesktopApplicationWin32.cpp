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

#include "application/DesktopApplication.h"

#include <dwmapi.h>

namespace
{

enum class Style : DWORD {
    windowed = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
    aero_borderless = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN,
};

}

namespace Vremenar
{

void DesktopApplication::setupTitleBarLessWindow(quintptr winId,
                                                 qreal devicePixelRatio)
{
    _nativeEventFilter = std::make_unique<NativeEventFilterWin32>(winId, devicePixelRatio);
    installNativeEventFilter(_nativeEventFilter.get());

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
    auto *wnd = reinterpret_cast<HWND>(winId);
    // enable borderless and keep aero effects.
    SetWindowLongPtr(wnd, GWL_STYLE, static_cast<LONG>(Style::aero_borderless));

    // enable shadow
    const MARGINS shadow_on = { 1, 1, 1, 1 };
    /*const MARGINS shadow_off = { 0, 0, 0, 0 };*/
    DwmExtendFrameIntoClientArea(wnd, &shadow_on);

    //redraw frame
    SetWindowPos(wnd, Q_NULLPTR, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
    ShowWindow(wnd, SW_SHOW);
}

void DesktopApplication::setPrimaryWindowDevicePixelRatio(qreal ratio)
{
    if (_nativeEventFilter != nullptr) {
        _nativeEventFilter->setPrimaryWindowDevicePixelRatio(ratio);
    }
}

} // namespace Vremenar
