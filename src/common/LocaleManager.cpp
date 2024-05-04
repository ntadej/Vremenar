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
#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QStringLiteral>
#include <QtCore/QTranslator>

#include <memory>

namespace Vremenar
{

LocaleManager::LocaleManager(QObject *parent)
    : QObject(parent),
      _translator(std::make_unique<QTranslator>())
{
    QCoreApplication::installTranslator(_translator.get());
    setLocale();
}

QStringList LocaleManager::loadLocales()
{
    const QDir dir(QStringLiteral(":/i18n/"));
    QStringList list;
    const QStringList entryList = dir.entryList(QDir::AllEntries);
    for (const QString &fileName : entryList) {
        if (fileName.contains(QStringLiteral(".qm"))) {
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
    f = f.remove(QStringLiteral(".qm"));

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
        setLanguageByString(settings.locale(), QStringLiteral("settings"));
        return;
    }

    // Try system UI languages
    const QStringList languages = QLocale::system().uiLanguages();
    for (const QString &lang : languages) {
        if (setLanguageByString(lang, QStringLiteral("UI"))) {
            return;
        }
    }

    // Use default language
    setLanguageByString(QStringLiteral("C"), QStringLiteral("default"));
}

bool LocaleManager::setLanguageByString(const QString &lang,
                                        const QString &source)
{
    const QLocale locale = QLocale(lang);
    qDebug() << "Trying language" << lang << "from source" << source;
    if (_translator->load(locale, QStringLiteral(":/i18n/"))) {
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
