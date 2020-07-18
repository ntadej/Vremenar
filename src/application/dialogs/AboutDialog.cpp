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

#include <QtCore/QDate>

#include "application/DesktopApplication.h"
#include "application/dialogs/AboutDialog.h"
#include "common/About.h"
#include "location/MapsCommon.h"

#include "Config.h"

namespace Vremenar
{

AboutDialog::AboutDialog(WeatherProviderBase *weatherProvider,
                         QWidget *parent)
    : QDialog(parent),
      ui(std::make_unique<Ui::AboutDialog>())
{
    ui->setupUi(this);

    setWindowTitle(tr("About %1").arg(Vremenar::name));
    setWindowFlags(Qt::Dialog
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);

    QString additionalStyle;
#ifdef Q_OS_MAC
    auto *application = qobject_cast<DesktopApplication *>(QCoreApplication::instance());
    if (application->isDark()) {
        additionalStyle.append("color: #cccccc;");
    }
#endif

    QString copyrightMaps;
    for (const std::unique_ptr<Hyperlink> &link : Maps::copyright()) {
        copyrightMaps.append(" " + link->asHtml(additionalStyle));
    }

    std::vector<std::unique_ptr<Hyperlink>> icons;
    icons.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© Ionicons"),
        QStringLiteral("https://ionicons.com")));
    icons.emplace_back(std::make_unique<Hyperlink>(
        QStringLiteral("© Breeze Icons"),
        QStringLiteral("https://github.com/KDE/breeze-icons")));

    QString copyrightIcons;
    for (const std::unique_ptr<Hyperlink> &link : icons) {
        copyrightIcons.append(" " + link->asHtml(additionalStyle));
    }

    QString aboutLabels;
    for (const std::unique_ptr<Hyperlink> &link : Vremenar::aboutLinks()) {
        if (link->mobileOnly()) {
            continue;
        }
        aboutLabels.append(" " + link->asHtml(additionalStyle));
    }

    auto homepage = std::make_unique<Hyperlink>(
        QStringLiteral("https://vremenar.tano.si"),
        QStringLiteral("https://vremenar.tano.si"));

    ui->labelVremenar->setText(QStringLiteral("Vremenar"));
    ui->labelVersion->setText(tr("Version %1 (%2)").arg(Vremenar::version, QString::number(Vremenar::build)));
    ui->labelCopyright->setText(QStringLiteral("© %1 Tadej Novak").arg(QDate::currentDate().toString(QStringLiteral("yyyy"))));
    ui->labelHomepage->setText(homepage->asHtml(additionalStyle));

    ui->labelWeather->setText(tr("Weather data") + " " + weatherProvider->copyrightLink()->asHtml(additionalStyle));
    ui->labelMaps->setText(tr("Maps") + copyrightMaps);
    ui->labelIcons->setText(tr("Icons") + copyrightIcons);
    ui->labelAbout->setText(aboutLabels);
}

} // namespace Vremenar
