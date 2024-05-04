/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "common/About.h"

#include "common/containers/Hyperlink.h"

#include <QtCore/QObject>
#include <QtCore/QStringLiteral>

#include <memory>
#include <vector>

namespace Vremenar
{

std::vector<std::unique_ptr<Hyperlink>> aboutLinks()
{
    std::vector<std::unique_ptr<Hyperlink>> list;
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("About Vremenar"),
        QStringLiteral("https://vremenar.app"),
        true));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Terms of Service"),
        QStringLiteral("https://vremenar.app/terms")));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Privacy Policy"),
        QStringLiteral("https://vremenar.app/privacy")));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Report an issue"),
        QStringLiteral("https://github.com/ntadej/Vremenar/issues")));
    return list;
}

} // namespace Vremenar
