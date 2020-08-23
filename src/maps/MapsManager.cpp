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

void MapsManager::mapChanged(Weather::MapRenderingType type,
                             const QString &url)
{
    if (type == _type && _type != Weather::TilesRendering) {
        return;
    }

    qDebug() << "Map type changed to" << type;

    if (_mapObject == nullptr && !getMapObject()) {
        return;
    }

    _type = type;

    QMetaObject::invokeMethod(_mapObject, "addParameters",
                              Q_ARG(QVariant, type),
                              Q_ARG(QString, url));
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
