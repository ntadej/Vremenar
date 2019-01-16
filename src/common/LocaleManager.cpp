/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QLocale>

#include "common/Resources.h"
#include "settings/Settings.h"

#include "common/LocaleManager.h"

namespace Vremenar
{

LocaleManager::LocaleManager(QObject *parent)
    : QObject(parent),
      _translator(std::make_unique<QTranslator>()),
      _locale("")
{
    QCoreApplication::installTranslator(_translator.get());
    setLocale();
}

LocaleManager::~LocaleManager()
{
    QCoreApplication::removeTranslator(_translator.get());
}

QStringList LocaleManager::loadLocales()
{
    QDir dir(":/i18n/");
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
    Settings settings(this);
    if (settings.locale().isEmpty()) {
        locale = QLocale::system().name();
    } else {
        locale = settings.locale();
    }

    qDebug() << "Using locale" << locale;

    QString langPath = Resources::path(":/i18n/" + locale + ".qm");
    _translator->load(locale, langPath);
    _locale = locale;

    emit localeChanged();
}

} // namespace Vremenar
