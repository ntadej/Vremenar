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

#include "common/LocaleManager.h"

#include "settings/Settings.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QLatin1StringView>
#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTranslator>

#include <memory>

using Qt::Literals::StringLiterals::operator""_L1;
using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

LocaleManager::LocaleManager(QObject *parent)
    : QObject(parent),
      _translator(std::make_unique<QTranslator>())
{
    QCoreApplication::installTranslator(_translator.get());

    qDebug() << "Available locales:" << loadLocales();

    setLocale();
}

QStringList LocaleManager::loadLocales()
{
    const QDir dir(u":/i18n/"_s);
    QStringList list;
    const QStringList entryList = dir.entryList(QDir::AllEntries);
    for (const QString &fileName : entryList) {
        if (fileName.contains(".qm"_L1)) {
            list << localeName(fileName);
        }
    }

    return list;
}

QString LocaleManager::localeName(const QString &file)
{
    const QLocale locale = QLocale(file);
    QString name = locale.name();
    QString f = file;
    f = f.remove(".qm"_L1).remove("vremenar_"_L1);

    if (name != f) {
        name = f;
    }

    return name;
}

void LocaleManager::setLocale()
{
    // Try settings first
    const Settings settings(this);
    if (!settings.locale().isEmpty()) {
        setLanguageByString(settings.locale(), u"settings"_s);
        return;
    }

    // Try system UI languages
    const QStringList languages = QLocale::system().uiLanguages();
    for (const QString &lang : languages) {
        if (setLanguageByString(lang, u"UI"_s)) {
            return;
        }
    }

    // Use default language
    setLanguageByString(u"C"_s, u"default"_s);
}

bool LocaleManager::setLanguageByString(const QString &lang,
                                        const QString &source)
{
    const QLocale locale = QLocale(lang);
    qDebug() << "Trying language" << lang << "from source" << source;
    if (_translator->load(locale, u":/i18n/"_s, u"vremenar_"_s)) {
        _locale = locale.name();

        qDebug() << "Using locale" << locale;

        emit localeChanged(_locale);

        return true;
    }

    return false;
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_LocaleManager.cpp"
// NOLINTEND
