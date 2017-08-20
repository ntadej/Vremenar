/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_LOCALEMANAGER_H_
#define VREMENAR_LOCALEMANAGER_H_

#include <QtCore/QString>
#include <QtCore/QTranslator>

class LocaleManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString R READ retranslateQml NOTIFY localeChanged)
    Q_PROPERTY(QString locale READ locale NOTIFY localeChanged)
public:
    LocaleManager(QObject *parent = nullptr);
    ~LocaleManager();

    static QStringList loadLocales();
    static QString localeName(const QString &file);

signals:
    void localeChanged();

public slots:
    void setLocale();

private:
    inline QString retranslateQml() { return ""; }
    inline QString locale() { return _locale; }

    QTranslator *_translator;
    QString _locale;
};

#endif // VREMENAR_LOCALEMANAGER_H_
