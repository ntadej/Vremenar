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

#ifndef VREMENAR_DESKTOPAPPLICATION_H_
#define VREMENAR_DESKTOPAPPLICATION_H_

#include "application/SingleApplication.h"

namespace Vremenar
{

class DesktopApplication : public SingleApplication
{
    Q_OBJECT
public:
    explicit DesktopApplication(int &argc, // NOLINT(google-runtime-references)
                                char **argv,
                                QObject *parent = nullptr);

    void postInit() const;

    bool eventFilter(QObject *object,
                     QEvent *event) override;

#ifdef Q_OS_MACOS
    bool isDark();

    void setupDockHandler();
    void setupTitleBarLessWindow(WId winId);

public Q_SLOTS:
    void dockClickedCallback();
    void dockSetVisibility(bool visible);
#endif

Q_SIGNALS:
    void urlOpened(const QString &);

#ifdef Q_OS_MACOS
    void dockClicked();

private:
    void dockShow();
    void dockHide();
#endif
};

} // namespace Vremenar

#endif // VREMENAR_DESKTOPAPPLICATION_H_
