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
#include <QtCore/QMetaObject>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>

#include "maps/MapsManager.h"

namespace Vremenar
{

MapsManager::MapsManager(QQmlApplicationEngine *engine,
                         QObject *parent)
    : QObject(parent),
      _engine(engine)
{
}

void MapsManager::mapChanged(Weather::MapType type,
                             Weather::MapRenderingType renderingType,
                             const QString &urlPrevious,
                             const QString &urlCurrent,
                             const QString &urlNext)
{
    if (_type != type) {
        qDebug() << "Map type changed to" << type;
    }

    if (_renderingType != renderingType) {
        qDebug() << "Map rendering type changed to" << type;
    }

    if (_mapObject == nullptr && !getMapObject()) {
        return;
    }

    _type = type;
    _renderingType = renderingType;

    QMetaObject::invokeMethod(_mapObject, "addParameters",
                              Q_ARG(QVariant, type),
                              Q_ARG(QVariant, renderingType),
                              Q_ARG(QString, urlPrevious),
                              Q_ARG(QString, urlCurrent),
                              Q_ARG(QString, urlNext));
}

bool MapsManager::getMapObject()
{
    auto *window = qobject_cast<QQuickWindow *>(_engine->rootObjects().constFirst());
    _mapObject = window->findChild<QObject *>(QStringLiteral("mapObject"));
    if (_mapObject != nullptr) {
        qDebug() << "Map object found";
        return true;
    }

    qDebug() << "Map object not found";
    return false;
}

} // namespace Vremenar

#include "moc_MapsManager.cpp"
