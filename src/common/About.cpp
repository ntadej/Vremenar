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
#include <QtCore/QString>

#include <memory>
#include <vector>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

std::vector<std::unique_ptr<Hyperlink>> aboutLinks()
{
    std::vector<std::unique_ptr<Hyperlink>> list;
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("About Vremenar"),
        u"https://vremenar.app"_s,
        true));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Terms of Service"),
        u"https://vremenar.app/terms"_s));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Privacy Policy"),
        u"https://vremenar.app/privacy"_s));
    list.emplace_back(std::make_unique<Hyperlink>(
        QObject::tr("Report an issue"),
        u"https://github.com/ntadej/Vremenar/issues"_s));
    return list;
}

} // namespace Vremenar
