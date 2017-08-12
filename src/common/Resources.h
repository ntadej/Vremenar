/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_RESOURCES_H_
#define VREMENAR_RESOURCES_H_

#include <QtCore/QString>

namespace Vremenar
{
    namespace Resources
    {
        // Resources locators
        QString path(const QString &file);
        QString resource(const QString &file);

        // Special locations
        QString appData();
    }
}

#endif // VREMENAR_RESOURCES_H_
