/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QTextCodec>
#include <QtGui/QFileOpenEvent>

#include "common/Common.h"
#include "common/Log.h"
#include "common/Output.h"

#include "DesktopApplication.h"

#ifdef Q_OS_MAC
#include <objc/objc.h>
#include <objc/message.h>

bool dockClickHandler(id self,
                      SEL cmd,
                      ...)
{
    Q_UNUSED(self)
    Q_UNUSED(cmd)

    ((DesktopApplication *)qApp)->onClickOnDock();

    return true;
}
#endif

DesktopApplication::DesktopApplication(int &argc,
                                       char **argv)
    : SingleApplication(argc, argv)
{
    installEventFilter(this);

#ifdef Q_OS_MAC
    setupDockHandler();
#endif
}

DesktopApplication::~DesktopApplication() {}

void DesktopApplication::preInit()
{
    QCoreApplication::setOrganizationDomain(Vremenar::domain());
    QCoreApplication::setApplicationName(Vremenar::name());
    QCoreApplication::setApplicationVersion(Vremenar::version());

    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    Vremenar::Log::setup();
}

void DesktopApplication::postInit()
{
    Vremenar::Output::welcome();
}

bool DesktopApplication::eventFilter(QObject *object,
                                     QEvent *event)
{
    if (event->type() == QEvent::FileOpen) {
        QFileOpenEvent *fileEvent = static_cast<QFileOpenEvent *>(event);
        if (!fileEvent->url().isEmpty()) {
            emit urlOpened(fileEvent->url().toString());
            return false;
        } else {
            return QObject::eventFilter(object, event);
        }
    } else {
        return QObject::eventFilter(object, event);
    }
}

void DesktopApplication::onClickOnDock()
{
    emit dockClicked();
}

#ifdef Q_OS_MAC
void DesktopApplication::setupDockHandler()
{
    Class cls = objc_getClass("NSApplication");
    objc_object *appInst = objc_msgSend((objc_object *)cls, sel_registerName("sharedApplication"));

    if (appInst != NULL) {
        objc_object *delegate = objc_msgSend(appInst, sel_registerName("delegate"));
        Class delClass = (Class)objc_msgSend(delegate, sel_registerName("class"));
        SEL shouldHandle = sel_registerName("applicationShouldHandleReopen:hasVisibleWindows:");
        if (class_getInstanceMethod(delClass, shouldHandle)) {
            if (class_replaceMethod(delClass, shouldHandle, (IMP)dockClickHandler, "B@:"))
                qDebug() << "Registered dock click handler (replaced original method)";
            else
                qWarning() << "Failed to replace method for dock click handler";
        } else {
            if (class_addMethod(delClass, shouldHandle, (IMP)dockClickHandler, "B@:"))
                qDebug() << "Registered dock click handler";
            else
                qWarning() << "Failed to register dock click handler";
        }
    }
}
#endif
