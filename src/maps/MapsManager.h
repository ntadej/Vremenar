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

#ifndef VREMENAR_MAPSMANAGER_H_
#define VREMENAR_MAPSMANAGER_H_

#include <QtCore/QObject>
#include <QtQml/QQmlApplicationEngine>

#include "weather/Weather.h"

namespace Vremenar
{

class MapsManager : public QObject
{
    Q_OBJECT
public:
    explicit MapsManager(QQmlApplicationEngine *engine,
                         QObject *parent = nullptr);

public slots:
    void mapChanged(Weather::MapType type,
                    Weather::MapRenderingType renderingType,
                    const QString &urlPrevious,
                    const QString &urlCurrent,
                    const QString &urlNext);

private:
    bool getMapObject();

    Weather::MapType _type{Weather::UnknownMapType};
    Weather::MapRenderingType _renderingType{Weather::IconsRendering};

    QQmlApplicationEngine *_engine{}; // not owned here
    QObject *_mapObject{};            // not owned here
};

} // namespace Vremenar

#endif // VREMENAR_MAPSMANAGER_H_
