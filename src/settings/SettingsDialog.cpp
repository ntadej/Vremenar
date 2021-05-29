/*
* Vremenar
* Copyright (C) 2021 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtWidgets/QMessageBox>

#include "application/BaseApplication.h"
#include "common/LocaleManager.h"
#include "settings/Settings.h"

#include "SettingsDialog.h"

namespace Vremenar
{

SettingsDialog::SettingsDialog(QWidget *parent)
    : QMainWindow(parent),
      ui(std::make_unique<Ui::SettingsDialog>())
{
    ui->setupUi(this);

    _latitudeValidator = std::make_unique<QDoubleValidator>(-90, 90, 4);    // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    _longitudeValidator = std::make_unique<QDoubleValidator>(-180, 180, 4); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ui->lineEditLatitude->setValidator(_latitudeValidator.get());
    ui->lineEditLongitude->setValidator(_longitudeValidator.get());

    _group = std::make_unique<QActionGroup>(this);
    _group->addAction(ui->actionGeneral);
    _group->addAction(ui->actionInterface);

    setWindowTitle(ui->actionGeneral->text());
    setWindowFlags(Qt::Window
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);

#if defined(Q_OS_MACOS)
    initializeMacOS();
#else
    connect(ui->actionGeneral, &QAction::toggled, this, &SettingsDialog::actionToggled);
    connect(ui->actionInterface, &QAction::toggled, this, &SettingsDialog::actionToggled);
#endif

    connect(ui->checkRememberPosition, &QCheckBox::toggled, this, &SettingsDialog::rememberPositionChangedSlot);
    connect(ui->checkRememberSize, &QCheckBox::toggled, this, &SettingsDialog::rememberSizeChangedSlot);

#ifdef Q_OS_MACOS
    connect(ui->checkShowInTray, &QCheckBox::toggled, this, &SettingsDialog::showInTrayChangedSlot);
    connect(ui->checkShowInDock, &QCheckBox::toggled, this, &SettingsDialog::showInDockChangedSlot);
#else
    ui->labelSpacerMacOS->hide();
    ui->checkShowInTray->hide();
    ui->checkShowInDock->hide();
#endif

    connect(ui->radioLocationAuto, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationSelect, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationCoord, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationDisabled, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->lineEditLatitude, &QLineEdit::textChanged, this, &SettingsDialog::locationLatitudeValidationChanged);
    connect(ui->lineEditLatitude, &QLineEdit::editingFinished, this, &SettingsDialog::locationCoordinateChanged);
    connect(ui->lineEditLongitude, &QLineEdit::textChanged, this, &SettingsDialog::locationLongitudeValidationChanged);
    connect(ui->lineEditLongitude, &QLineEdit::editingFinished, this, &SettingsDialog::locationCoordinateChanged);

    readSettings();
    loadLocales();
    loadSources();

#ifndef Q_OS_MACOS
    // Set application icon
    QIcon icon;
    icon.addFile(":/Vremenar/Icons/16x16/preferences-system.png", QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(":/Vremenar/Icons/24x24/preferences-system.png", QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(":/Vremenar/Icons/32x32/preferences-system.png", QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(":/Vremenar/Icons/48x48/preferences-system.png", QSize(48, 48)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(":/Vremenar/Icons/64x64/preferences-system.png", QSize(64, 64)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    setWindowIcon(icon);
#endif
}

void SettingsDialog::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
#if defined(Q_OS_MACOS)
        retranslateMacOS();
#endif
        loadLocales();
        loadSources();
        break;
    default:
        break;
    }
}

void SettingsDialog::actionToggled()
{
#if defined(Q_OS_MACOS)
    actionToggledMacOS();
#else
    QAction *action = qobject_cast<QAction *>(sender());

    setWindowTitle(action->text());
    if (action == ui->actionGeneral) {
        ui->stackedWidget->setCurrentWidget(ui->pageGeneral);
    } else if (action == ui->actionInterface) {
        ui->stackedWidget->setCurrentWidget(ui->pageInterface);
    }
#endif
}

void SettingsDialog::readSettings()
{
    Settings settings(this);

#ifdef Q_OS_MACOS
    ui->checkShowInTray->setChecked(settings.showInTray());
    ui->checkShowInDock->setChecked(settings.showInDock());
#endif
    ui->checkRememberPosition->setChecked(settings.rememberPosition());
    ui->checkRememberSize->setChecked(settings.rememberSize());

    // Location
    switch (settings.locationSource()) {
    case Location::Automatic:
        ui->radioLocationAuto->setChecked(true);
        break;
    case Location::Station:
        ui->radioLocationSelect->setChecked(true);
        ui->comboLocation->setEnabled(true);
        break;
    case Location::Coordinate:
        ui->radioLocationCoord->setChecked(true);
        ui->lineEditLatitude->setEnabled(true);
        ui->lineEditLongitude->setEnabled(true);
        break;
    case Location::Disabled:
        ui->radioLocationDisabled->setChecked(true);
        break;
    }

    if (settings.locationLatitude() != 0 || settings.locationLongitude() != 0) {
        QLocale locale;
        ui->lineEditLatitude->setText(locale.toString(settings.locationLatitude()));
        ui->lineEditLongitude->setText(locale.toString(settings.locationLongitude()));
    }
}

void SettingsDialog::localeChangedSlot()
{
    Settings settings(this);
    if (ui->comboLocale->currentIndex() == 0) {
        settings.setLocale(QString());
    } else {
        settings.setLocale(_locales[ui->comboLocale->currentIndex() - 1]);
    }
    settings.writeSettings();

    Q_EMIT localeChanged();
}

void SettingsDialog::locationChangedSlot()
{
    Settings settings(this);
    if (ui->radioLocationAuto->isChecked()) {
        settings.setLocationSource(Location::Automatic);
    } else if (ui->radioLocationSelect->isChecked()) {
        settings.setLocationSource(Location::Station);
    } else if (ui->radioLocationCoord->isChecked()) {
        settings.setLocationSource(Location::Coordinate);
    } else if (ui->radioLocationDisabled->isChecked()) {
        settings.setLocationSource(Location::Disabled);
    }
    settings.writeSettings();

    ui->comboLocation->setEnabled(settings.locationSource() == Location::Station);
    ui->lineEditLatitude->setEnabled(settings.locationSource() == Location::Coordinate);
    ui->lineEditLongitude->setEnabled(settings.locationSource() == Location::Coordinate);

    Q_EMIT locationChanged();
}

void SettingsDialog::locationCoordinateChanged()
{
    Settings settings(this);
    QLocale locale;
    if (ui->lineEditLatitude->hasAcceptableInput()) {
        settings.setLocationLatitude(locale.toDouble(ui->lineEditLatitude->text()));
    }
    if (ui->lineEditLongitude->hasAcceptableInput()) {
        settings.setLocationLongitude(locale.toDouble(ui->lineEditLongitude->text()));
    }
    settings.writeSettings();
    Q_EMIT locationChanged();
}

void SettingsDialog::locationLatitudeValidationChanged()
{
    if (!ui->lineEditLatitude->text().isEmpty() && !ui->lineEditLatitude->hasAcceptableInput()) {
        ui->lineEditLatitude->setStyleSheet(QStringLiteral("color: red;"));
    } else {
        ui->lineEditLatitude->setStyleSheet(QString());
    }
}

void SettingsDialog::locationLongitudeValidationChanged()
{
    if (!ui->lineEditLongitude->text().isEmpty() && !ui->lineEditLongitude->hasAcceptableInput()) {
        ui->lineEditLongitude->setStyleSheet(QStringLiteral("color: red;"));
    } else {
        ui->lineEditLongitude->setStyleSheet(QString());
    }
}

void SettingsDialog::locationStationChanged()
{
}

void SettingsDialog::sourceChangedSlot()
{
    QMessageBox::information(this, tr("Weather source changed"),
                             tr("The weather source has been changed.\n"
                                "The application will now restart."),
                             QMessageBox::Ok);

    Q_EMIT weatherSourceChanged(ui->comboSource->currentIndex());
}

void SettingsDialog::loadLocales()
{
    Settings settings(this);

    disconnect(ui->comboLocale, &QComboBox::currentTextChanged, this, &SettingsDialog::localeChangedSlot);

    _locales = LocaleManager::loadLocales();

    ui->comboLocale->clear();
    ui->comboLocale->addItem(tr("System default"));
    for (const QString &locale : qAsConst(_locales)) {
        ui->comboLocale->addItem(QLocale(locale).nativeLanguageName());
        if (settings.locale() == locale) {
            ui->comboLocale->setCurrentIndex(ui->comboLocale->count() - 1);
        }
    }

    connect(ui->comboLocale, &QComboBox::currentTextChanged, this, &SettingsDialog::localeChangedSlot);
}

void SettingsDialog::loadSources()
{
    Settings settings(this);

    disconnect(ui->comboSource, &QComboBox::currentTextChanged, this, &SettingsDialog::sourceChangedSlot);

    ui->comboSource->clear();
    for (Sources::Country country : {Sources::Slovenia, Sources::Germany}) {
        ui->comboSource->addItem(Sources::countryToLocalizedString(country));
        if (settings.weatherSource() == country) {
            ui->comboSource->setCurrentIndex(ui->comboSource->count() - 1);
        }
    }

    connect(ui->comboSource, &QComboBox::currentTextChanged, this, &SettingsDialog::sourceChangedSlot);
}

#ifdef Q_OS_MACOS
void SettingsDialog::showInTrayChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setShowInTray(checked);
    settings.writeSettings();

    Q_EMIT showInTrayChanged(checked);

    ui->checkShowInDock->setEnabled(checked);
    if (!checked) {
        ui->checkShowInDock->setChecked(true);
    }
}

void SettingsDialog::showInDockChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setShowInDock(checked);
    settings.writeSettings();

    Q_EMIT showInDockChanged(checked);
}
#endif

void SettingsDialog::rememberPositionChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setRememberPosition(checked);
    settings.writeSettings();
}

void SettingsDialog::rememberSizeChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setRememberSize(checked);
    settings.writeSettings();
}

} // namespace Vremenar
