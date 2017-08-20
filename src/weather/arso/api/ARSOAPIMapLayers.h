/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOAPIMAPLAYERS_H_
#define VREMENAR_ARSOAPIMAPLAYERS_H_

#include "weather/common/Weather.h"
#include "weather/arso/api/ARSOAPIRequest.h"

namespace Vremenar
{
    namespace ARSO
    {
        ARSOAPIRequest mapLayers(Vremenar::Weather::MapType type);
    }
}

#endif // VREMENAR_ARSOAPIMAPLAYERS_H_
