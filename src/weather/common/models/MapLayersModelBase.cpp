/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "weather/common/models/MapLayersModelBase.h"

namespace Vremenar
{

MapLayersModelBase::MapLayersModelBase(QObject *parent)
    : ListModel(MapLayer::roleNames(), parent) {}

} // namespace Vremenar
