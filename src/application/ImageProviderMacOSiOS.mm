/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include "application/ImageProviderMacOSiOS.h"

#include <QtGui/QColor>
#include <QtGui/private/qcoregraphics_p.h>

#if defined(Q_OS_MACOS)
#import <AppKit/AppKit.h>
#elif defined(Q_OS_IOS)
#import <UIKit/UIKit.h>
#endif

#if defined(Q_OS_IOS)
namespace
{

UIImage *imageWithColor(UIColor *color,
                        UIImage *image)
{
    // Begin drawing
    CGRect rect = CGRectMake(0.f, 0.f, image.size.width, image.size.height);
    UIGraphicsBeginImageContextWithOptions(image.size, NO, image.scale);

    [color set];
    [[image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate] drawInRect:rect];

    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();

    return img;
}

} // namespace
#endif

namespace Vremenar
{

SFSymbolsImageProvider::SFSymbolsImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    QImage testImage = requestImage("play.fill/UltraLight/1", nullptr, QSize(14, 14)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    if (testImage.width() < 24) {                                                      // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        _scale = 24. / testImage.width();
    }
}

QImage SFSymbolsImageProvider::requestImage(const QString &id,
                                            QSize *size,
                                            const QSize &requestedSize)
{
    QStringList idSplit = id.split(QStringLiteral("/"));

    CGImageRef cgImage{};
#if defined(Q_OS_MACOS)
    if (@available(macOS 11.0, *)) {
        QColor color(idSplit[1]);
        NSFontWeight nsFontWeight = idSplit[2] == QStringLiteral("UltraLight") ? NSFontWeightUltraLight : NSFontWeightRegular;
        auto nsColor = [NSColor colorWithRed:color.redF() green:color.greenF() blue:color.blueF() alpha:1.];
        auto nsConfig = [NSImageSymbolConfiguration configurationWithPointSize:(requestedSize.width() * _scale) weight:nsFontWeight];
        auto nsImage = [NSImage imageWithSystemSymbolName:idSplit[0].toNSString() accessibilityDescription:nil];
        nsImage = [nsImage imageWithSymbolConfiguration:nsConfig];
        [nsImage lockFocus];
        [nsColor set];
        NSRect imageRect = {NSZeroPoint, [nsImage size]};
        NSRectFillUsingOperation(imageRect, NSCompositingOperationSourceIn);
        [nsImage unlockFocus];
        cgImage = [nsImage CGImageForProposedRect:nil context:nil hints:nil];
    }
#elif defined(Q_OS_IOS)
    if (@available(iOS 13.0, *)) {
        QColor color(idSplit[1]);
        UIImageSymbolWeight uiWeight = idSplit[2] == QStringLiteral("UltraLight") ? UIImageSymbolWeightUltraLight : UIImageSymbolWeightRegular;
        double devicePixelRatio = idSplit[3].toDouble();
        int width = devicePixelRatio >= 3 ? requestedSize.width() / 7 * 5 : requestedSize.width();
        auto uiColor = [UIColor colorWithRed:color.redF() green:color.greenF() blue:color.blueF() alpha:1.];
        auto uiConfig = [UIImageSymbolConfiguration configurationWithPointSize:width weight:uiWeight];
        auto uiImage = [UIImage systemImageNamed:idSplit[0].toNSString() withConfiguration:uiConfig];
        uiImage = imageWithColor(uiColor, uiImage);
        cgImage = [uiImage CGImage];
    }
#endif

    QImage image = qt_mac_toQImage(cgImage);
    if (size != nullptr) {
        *size = image.size();
    }

    return image;
}

} // namespace Vremenar
