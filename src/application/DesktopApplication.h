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

#ifndef VREMENAR_DESKTOPAPPLICATION_H_
#define VREMENAR_DESKTOPAPPLICATION_H_

#include "application/SingleApplication.h"

#if defined(Q_OS_WINDOWS)
#include "application/NativeEventFilterWin32.h"
#endif

namespace Vremenar
{

class DesktopApplication : public SingleApplication
{
    Q_OBJECT
public:
    static DesktopApplication init(int &argc, // NOLINT(google-runtime-references)
                                   char **argv);

    bool eventFilter(QObject *object,
                     QEvent *event) override;

#if defined(Q_OS_MACOS) || (QT_VERSION < QT_VERSION_CHECK(6, 0, 0) && defined(Q_OS_WINDOWS))
    void setupTitleBarLessWindow(quintptr winId,
                                 qreal devicePixelRatio = 1.0);
#endif

#if defined(Q_OS_MACOS)
    bool isDark();
    static bool supportsSFSymbols();

    void setupDockHandler();

public slots:
    void dockClickedCallback();
    void dockSetVisibility(bool visible);
#elif QT_VERSION < QT_VERSION_CHECK(6, 0, 0) && defined(Q_OS_WINDOWS)
    void setPrimaryWindowDevicePixelRatio(qreal ratio);
#endif

signals:
    void urlOpened(const QString &);

#if defined(Q_OS_MACOS)
    void dockClicked();

private:
    void dockShow();
    void dockHide();
#endif

private:
    explicit DesktopApplication(int &argc, // NOLINT(google-runtime-references)
                                char **argv,
                                QObject *parent = nullptr);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0) && defined(Q_OS_WINDOWS)
private:
    std::unique_ptr<NativeEventFilterWin32> _nativeEventFilter{};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_DESKTOPAPPLICATION_H_
