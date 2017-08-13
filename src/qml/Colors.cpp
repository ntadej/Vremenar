/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "qml/Colors.h"

QColor Colors::base() const { return QColor("#3E96F3"); }
QColor Colors::baseLight() const { return QColor("#5AC8FB"); }
QColor Colors::baseDark() const { return QColor("#3169DA"); }

QObject *Colors::provider(QQmlEngine *engine,
                          QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Colors;
}
