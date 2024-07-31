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

#include "application/dialogs/AboutDialog.h"

#include "common/About.h"
#include "common/containers/Hyperlink.h"
#include "maps/MapsCommon.h"
#include "weather/WeatherProvider.h"

#include "Config.h"

#include <QtCore/QDate>
#include <QtCore/QString>
#include <QtWidgets/QDialog>

#include <memory>
#include <vector>

using Qt::Literals::StringLiterals::operator""_s;

namespace Vremenar
{

AboutDialog::AboutDialog(WeatherProvider *weatherProvider,
                         QWidget *parent)
    : QDialog(parent),
      ui(std::make_unique<Ui::AboutDialog>())
{
    ui->setupUi(this);

    setWindowTitle(tr("About Vremenar"));
    setWindowFlags(Qt::Dialog
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);

    const QString additionalStyle;

    QString copyrightMaps;
    for (const std::unique_ptr<Hyperlink> &link : Maps::copyright()) {
        copyrightMaps.append(" " + link->asHtml(additionalStyle));
    }

    std::vector<std::unique_ptr<Hyperlink>> icons;
    icons.emplace_back(std::make_unique<Hyperlink>(
        u"© Ionicons"_s,
        u"https://ionicons.com"_s));
    icons.emplace_back(std::make_unique<Hyperlink>(
        u"© Breeze Icons"_s,
        u"https://github.com/KDE/breeze-icons"_s));

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
        u"https://vremenar.app"_s,
        u"https://vremenar.app"_s);

    ui->labelVremenar->setText(tr("Vremenar Weather"));
    ui->labelVersion->setText(tr("Version %1 (%2)").arg(Vremenar::version, QString::number(Vremenar::build)));
    ui->labelCopyright->setText(u"© %1 Tadej Novak"_s.arg(QDate::currentDate().toString(u"yyyy"_s)));
    ui->labelHomepage->setText(homepage->asHtml(additionalStyle));

    ui->labelWeather->setText(tr("Weather data") + " " + weatherProvider->copyrightLink()->asHtml(additionalStyle));
    ui->labelMaps->setText(tr("Maps") + copyrightMaps);
    ui->labelIcons->setText(tr("Icons") + copyrightIcons);
    ui->labelAbout->setText(aboutLabels);

#ifdef Q_OS_MACOS
    ui->buttons->hide();
#else
    connect(ui->buttons, &QDialogButtonBox::accepted, this, &AboutDialog::close);
#endif
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_AboutDialog.cpp"
// NOLINTEND
