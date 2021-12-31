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

#include "application/NativeEventFilterWin32.h"

#include <QtCore/QByteArray>

#include <Windows.h>
#include <windowsx.h>

namespace Vremenar
{

NativeEventFilterWin32::NativeEventFilterWin32(quintptr winId)
    : _winId(winId)
{
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
bool NativeEventFilterWin32::nativeEventFilter(const QByteArray &eventType,
                                               void *message,
                                               long *result) // NOLINT(google-runtime-int)
{
    if (eventType.compare("windows_generic_MSG") == 0) {
        MSG* msg = static_cast<MSG *>(message);
        if (msg == Q_NULLPTR) {
            return false;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
        if (reinterpret_cast<quintptr>(msg->hwnd) != _winId) {
            return false;
        }

        switch(msg->message) {
        case WM_COMMAND: {
          SendMessage(msg->hwnd, WM_SYSCOMMAND, msg->wParam, msg->lParam);
          *result = DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
          return true;
        }
        case WM_NCCALCSIZE:{
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, performance-no-int-to-ptr)
            auto *params = reinterpret_cast<NCCALCSIZE_PARAMS *>(msg->lParam);
            if (params->rgrc[0].top != 0) {
                params->rgrc[0].top -= 1;
            }

            // this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
            *result = WVR_REDRAW;
            return true;
        }
        case WM_NCHITTEST: {
            const LONG borderWidth = 8; //in pixels
            RECT winrect;
            GetWindowRect(msg->hwnd, &winrect);
            int32_t x = GET_X_LPARAM(msg->lParam);
            int32_t y = GET_Y_LPARAM(msg->lParam);

            // caption, a.k.a. title bar
            auto wndScaleFactor = qgetenv("QT_SCALE_FACTOR").toDouble(); // TODO(tadej): do properly
            int titleBarHeight = 40;                                     // TODO(tadej): configurable
            titleBarHeight = static_cast<int>(titleBarHeight * wndScaleFactor);
            int titleBarBtnsWidth = 100; // TODO(tadej): configurable
            titleBarBtnsWidth = static_cast<int>(titleBarBtnsWidth * wndScaleFactor);
            if (x >= winrect.left && x < winrect.right - titleBarBtnsWidth &&
                    y > winrect.top + borderWidth && y < winrect.top + titleBarHeight) {
                *result = HTCAPTION;
                return true;
            }
            // bottom left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOMLEFT;
                return true;
            }
            // bottom right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOMRIGHT;
                return true;
            }
            // top left corner
            if (x >= winrect.left && x < winrect.left + borderWidth &&
                y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOPLEFT;
                return true;
            }
            // top right corner
            if (x < winrect.right && x >= winrect.right - borderWidth &&
                y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOPRIGHT;
                return true;
            }
            // left border
            if (x >= winrect.left && x < winrect.left + borderWidth) {
                *result = HTLEFT;
                return true;
            }
            // right border
            if (x < winrect.right && x >= winrect.right - borderWidth) {
                *result = HTRIGHT;
                return true;
            }
            // bottom border
            if (y < winrect.bottom && y >= winrect.bottom - borderWidth) {
                *result = HTBOTTOM;
                return true;
            }
            // top border
            if (y >= winrect.top && y < winrect.top + borderWidth) {
                *result = HTTOP;
                return true;
            }
            return false;
        }
        default:
            break;
        }
    }

    return false;
}

} // namespace Vremenar
