/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_ARSOAPIREQUEST_H_
#define VREMENAR_ARSOAPIREQUEST_H_

#include "weather/common/api/APIRequest.h"

class ARSOAPIRequest : public APIRequest
{
public:
    ARSOAPIRequest();
    ~ARSOAPIRequest();
};

#endif // VREMENAR_ARSOAPIREQUEST_H_
