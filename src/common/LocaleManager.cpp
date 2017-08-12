/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QLocale>

#include "common/LocaleManager.h"
#include "common/Resources.h"
#include "settings/Settings.h"

LocaleManager::LocaleManager(QObject *parent)
    : QObject(parent)
{
    _translator = new QTranslator();
    _locale = "";
    QCoreApplication::installTranslator(_translator);
    setLocale();
}

LocaleManager::~LocaleManager()
{
    QCoreApplication::removeTranslator(_translator);
    delete _translator;
}

QStringList LocaleManager::loadLocales()
{
    QDir dir(Vremenar::Resources::path("/i18n/sl_SI.qm"));
    QStringList list;
    list << QLocale(QLocale::English, QLocale::UnitedStates).name();

    for (const QString &fileName : dir.entryList(QDir::AllEntries)) {
        if (fileName.contains(".qm")) {
            list << localeName(fileName);
        }
    }

    return list;
}

QString LocaleManager::localeName(const QString &file)
{
    QLocale locale = QLocale(file);
    QString name = locale.name();
    QString f = file;
    f = f.replace(".qm", "");

    if (name != f)
        name = f;

    return name;
}

void LocaleManager::setLocale()
{
    QString locale;
    QScopedPointer<Settings> settings(new Settings(this));
    if (settings->locale().isEmpty()) {
        locale = QLocale::system().name();
    } else {
        locale = settings->locale();
    }

    qDebug() << "Using locale" << locale;

    QString langPath = Vremenar::Resources::path("/i18n/" + locale + ".qm");
    _translator->load(locale, langPath);
    _locale = locale;

    emit localeChanged();
}
