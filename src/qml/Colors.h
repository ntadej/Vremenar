/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_QML_COLORS_H_
#define VREMENAR_QML_COLORS_H_

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

class Colors : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor base READ base CONSTANT)
    Q_PROPERTY(QColor baseLight READ baseLight CONSTANT)
    Q_PROPERTY(QColor baseDark READ baseDark CONSTANT)

public:
    QColor base() const;
    QColor baseLight() const;
    QColor baseDark() const;

    static QObject *provider(QQmlEngine *engine,
                             QJSEngine *scriptEngine);
};

#endif // VREMENAR_QML_COLORS_H_
