/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_APIALERTS_H_
#define VREMENAR_APIALERTS_H_

#include "weather/api/APIRequest.h"

namespace Vremenar::API
{

APIRequest alerts(const QStringList &alertsAreas);

} // namespace Vremenar::API

#endif // VREMENAR_APIALERTS_H_
