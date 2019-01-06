/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "qml/Colors.h"

namespace Vremenar
{

QColor Qml::Colors::base() const { return {62, 150, 243, 1}; }
QColor Qml::Colors::baseLight() const { return {90, 200, 251, 1}; }
QColor Qml::Colors::baseDark() const { return {49, 105, 218, 1}; }

QObject *Qml::Colors::provider(QQmlEngine *engine,
                               QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Colors;
}

} // namespace Vremenar
