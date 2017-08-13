/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_DESKTOPAPPLICATION_H_
#define VREMENAR_DESKTOPAPPLICATION_H_

#include "SingleApplication.h"

class QWindow;

class DesktopApplication : public SingleApplication
{
    Q_OBJECT
public:
    explicit DesktopApplication(int &argc,
                                char **argv);
    ~DesktopApplication();

    static void preInit();
    void postInit();

    bool eventFilter(QObject *object,
                     QEvent *event);

#ifdef Q_OS_MAC
    void setupDockHandler();
    void setupTitleBarLessWindow(WId winId);

public slots:
    void dockClickedCallback();
    void dockSetVisibility(bool visible);
#endif

signals:
    void urlOpened(const QString &);

#ifdef Q_OS_MAC
    void dockClicked();

private:
    void dockShow();
    void dockHide();
#endif
};

#endif // VREMENAR_DESKTOPAPPLICATION_H_
