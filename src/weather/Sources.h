/*
* Vremenar
* Copyright (C) 2020 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_SOURCES_H_
#define VREMENAR_SOURCES_H_

#include <QtCore/QObject>
#include <QtCore/QUrlQuery>

namespace Vremenar::Sources
{

Q_NAMESPACE

enum Country {
    Slovenia,
    Germany
};

Q_ENUM_NS(Country)

Country countryFromString(const QString &country);
QString countryToString(Vremenar::Sources::Country country);
Q_INVOKABLE QString countryToLocalizedString(Vremenar::Sources::Country country);

QUrlQuery sourceQuery();

} // namespace Vremenar::Sources

#endif // VREMENAR_SOURCES_H_
