/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "qml/UIManager.h"

namespace Vremenar
{

QObject *Qml::UIManager::provider(QQmlEngine *engine,
                                  QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new UIManager;
}

} // namespace Vremenar
