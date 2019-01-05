/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_HELPERS_H_
#define VREMENAR_HELPERS_H_

#include <QtCore/QtCore>

namespace Vremenar
{

template <class T, class U>
inline std::unique_ptr<T> qobject_pointer_cast(U *object)
{
    return std::unique_ptr<T>(qobject_cast<T *>(object));
}

} // namespace Vremenar

#endif // VREMENAR_HELPERS_H_
