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

#ifndef VREMENAR_LOCALEMANAGER_H_
#define VREMENAR_LOCALEMANAGER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTranslator>

#include <memory>

namespace Vremenar
{

class LocaleManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString R READ retranslateQml NOTIFY localeChanged)
    Q_PROPERTY(QString locale READ locale NOTIFY localeChanged)
public:
    explicit LocaleManager(QObject *parent = nullptr);

    static QStringList loadLocales();
    static QString localeName(const QString &file);

    [[nodiscard]] const QString &locale() const { return _locale; }

signals:
    void localeChanged(const QString &locale); // NOLINT(readability-inconsistent-declaration-parameter-name)

public slots:
    void setLocale();

private:
    [[nodiscard]] QString retranslateQml() const { return {}; }

    bool setLanguageByString(const QString &lang,
                             const QString &source);

    std::unique_ptr<QTranslator> _translator;
    QString _locale;
};

} // namespace Vremenar

#endif // VREMENAR_LOCALEMANAGER_H_
