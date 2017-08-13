/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_QML_GLOBALS_H_
#define VREMENAR_QML_GLOBALS_H_

#include <QtCore/QObject>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlEngine>

class Globals : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(int build READ build CONSTANT)

    Q_PROPERTY(QString locationProviderAppId READ locationProviderAppId CONSTANT)
    Q_PROPERTY(QString locationProviderAppToken READ locationProviderAppToken CONSTANT)

public:
    QString name() const;
    QString version() const;
    int build() const;

    QString locationProviderAppId() const;
    QString locationProviderAppToken() const;

    static QObject *provider(QQmlEngine *engine,
                             QJSEngine *scriptEngine);
    static QObject *providerSettings(QQmlEngine *engine,
                                     QJSEngine *scriptEngine);
};

#endif // VREMENAR_QML_GLOBALS_H_
