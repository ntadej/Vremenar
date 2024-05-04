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

#ifndef VREMENAR_IMAGEPROVIDERMACOSIOS_H_
#define VREMENAR_IMAGEPROVIDERMACOSIOS_H_

#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtGui/QImage>
#include <QtQuick/QQuickImageProvider>

namespace Vremenar
{

class SFSymbolsImageProvider final : public QQuickImageProvider // clazy:exclude=ctor-missing-parent-argument,missing-qobject-macro
{
    Q_DISABLE_COPY_MOVE(SFSymbolsImageProvider)
public:
    explicit SFSymbolsImageProvider();
    ~SFSymbolsImageProvider() final = default;

    QImage requestImage(const QString &id,
                        QSize *size,
                        const QSize &requestedSize) final;

#if defined(Q_OS_MACOS)
private:
    double _scale{1.};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_IMAGEPROVIDERMACOSIOS_H_
