/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_QML_UIMANAGER_H_
#define VREMENAR_QML_UIMANAGER_H_

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

namespace Vremenar
{
namespace Qml
{

class UIManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor colorPrimary READ colorPrimary CONSTANT)
    Q_PROPERTY(QColor colorPrimaryLight READ colorPrimaryLight CONSTANT)
    Q_PROPERTY(QColor colorPrimaryDark READ colorPrimaryDark CONSTANT)

    Q_PROPERTY(QColor separatorColor READ separatorColor CONSTANT)

    Q_PROPERTY(int blurLevel READ blurLevel CONSTANT)

    Q_PROPERTY(int buttonMapSize READ buttonMapSize CONSTANT)

    Q_PROPERTY(int iconSizeCommon READ iconSizeCommon CONSTANT)
    Q_PROPERTY(int lineThickness READ lineThickness CONSTANT)
    Q_PROPERTY(int paddingCommon READ paddingCommon CONSTANT)
    Q_PROPERTY(int paddingHeader READ paddingHeader CONSTANT)
    Q_PROPERTY(int radiusCommon READ radiusCommon CONSTANT)

    Q_PROPERTY(int rowHeight READ rowHeight CONSTANT)
    Q_PROPERTY(QColor navBarColor READ navBarColor CONSTANT)
    Q_PROPERTY(int navBarHeight READ navBarHeight CONSTANT)

    Q_PROPERTY(int bottomSheetBaseHeight READ bottomSheetBaseHeight CONSTANT)
    Q_PROPERTY(int bottomSheetMaxWidth READ bottomSheetMaxWidth CONSTANT)

    Q_PROPERTY(int textCommon READ textCommon CONSTANT)
    Q_PROPERTY(int textHeader READ textHeader CONSTANT)
    Q_PROPERTY(QColor textColor READ textColor CONSTANT)
    Q_PROPERTY(QColor textColorPrimary READ textColorPrimary CONSTANT)

    Q_PROPERTY(QColor hoverColor READ hoverColor CONSTANT)
    Q_PROPERTY(int hoverDuration READ hoverDuration CONSTANT)

public:
    QColor colorPrimary() const;
    QColor colorPrimaryLight() const;
    QColor colorPrimaryDark() const;

    QColor separatorColor() const;

    int blurLevel() const;

    int buttonMapSize() const;

    int iconSizeCommon() const;
    int lineThickness() const;
    int paddingCommon() const;
    int paddingHeader() const;
    int radiusCommon() const;

    int rowHeight() const;
    QColor navBarColor() const;
    int navBarHeight() const;

    int bottomSheetBaseHeight() const;
    int bottomSheetMaxWidth() const;

    int textCommon() const;
    int textHeader() const;
    QColor textColor() const;
    QColor textColorPrimary() const;

    QColor hoverColor() const;
    int hoverDuration() const;

    static QObject *provider(QQmlEngine *engine,
                             QJSEngine *scriptEngine);
};

} // namespace Qml
} // namespace Vremenar

#endif // VREMENAR_QML_UIMANAGER_H_
