/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_NATIVEEVENTFILTERWIN32_H_
#define VREMENAR_NATIVEEVENTFILTERWIN32_H_

#include <QtCore/QAbstractNativeEventFilter>

namespace Vremenar
{

class NativeEventFilterWin32 : public QAbstractNativeEventFilter
{
public:
    explicit NativeEventFilterWin32(quintptr winId,
                                    qreal devicePixelRatio);

    bool nativeEventFilter(const QByteArray &eventType,
                           void *message,
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                           qintptr *result) override;
#else
                           long *result) override; // NOLINT(google-runtime-int)
#endif
    void setPrimaryWindowDevicePixelRatio(qreal ratio);

private:
    quintptr _winId;
    qreal _devicePixelRatio{1.0};
};

} // namespace Vremenar

#endif // VREMENAR_NATIVEEVENTFILTERWIN32_H_
