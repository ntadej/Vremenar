/*
* Vremenar
* Copyright (C) 2023 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#include <QtWidgets/QMessageBox>

#include "common/LocaleManager.h"
#include "settings/Settings.h"
#include "weather/containers/StationInfo.h"
#include "weather/models/StationListModel.h"

#include "SettingsDialog.h"

namespace Vremenar
{

SettingsDialog::SettingsDialog(StationListModel *stationsModel,
                               bool notificationsSupported,
                               QWidget *parent)
    : QMainWindow(parent),
      ui(std::make_unique<Ui::SettingsDialog>())
{
    ui->setupUi(this);

    _stationsCompleter = std::make_unique<QCompleter>(stationsModel, this);
    _stationsCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->comboLocation->setModel(stationsModel);
    ui->comboLocation->setCompleter(_stationsCompleter.get());
    ui->comboLocation->setInsertPolicy(QComboBox::NoInsert);
    _latitudeValidator = std::make_unique<QDoubleValidator>(-90, 90, 4);    // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    _longitudeValidator = std::make_unique<QDoubleValidator>(-180, 180, 4); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    ui->lineEditLatitude->setValidator(_latitudeValidator.get());
    ui->lineEditLongitude->setValidator(_longitudeValidator.get());

    _group = std::make_unique<QActionGroup>(this);
    _group->addAction(ui->actionGeneral);
    _group->addAction(ui->actionNotifications);
    _group->addAction(ui->actionInterface);

    setWindowTitle(ui->actionGeneral->text());
    setWindowFlags(Qt::Window
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);

#if defined(Q_OS_MACOS)
    initializeMacOS(notificationsSupported);
#else
    connect(ui->actionGeneral, &QAction::toggled, this, &SettingsDialog::actionToggled);
    connect(ui->actionNotifications, &QAction::toggled, this, &SettingsDialog::actionToggled);
    connect(ui->actionInterface, &QAction::toggled, this, &SettingsDialog::actionToggled);
#endif

    connect(ui->checkNotifications, &QCheckBox::toggled, this, &SettingsDialog::notificationsEnabledChangedSlot);
    connect(ui->radioAlertsExtreme, &QRadioButton::clicked, this, &SettingsDialog::notificationsSeverityChangedSlot);
    connect(ui->radioAlertsMinor, &QRadioButton::clicked, this, &SettingsDialog::notificationsSeverityChangedSlot);
    connect(ui->radioAlertsModerate, &QRadioButton::clicked, this, &SettingsDialog::notificationsSeverityChangedSlot);
    connect(ui->radioAlertsSevere, &QRadioButton::clicked, this, &SettingsDialog::notificationsSeverityChangedSlot);

    connect(ui->checkRememberPosition, &QCheckBox::toggled, this, &SettingsDialog::rememberPositionChangedSlot);
    connect(ui->checkRememberSize, &QCheckBox::toggled, this, &SettingsDialog::rememberSizeChangedSlot);

    connect(ui->checkShowInTray, &QCheckBox::toggled, this, &SettingsDialog::showInTrayChangedSlot);
#ifdef Q_OS_MACOS
    connect(ui->checkShowInDock, &QCheckBox::toggled, this, &SettingsDialog::showInDockChangedSlot);
#else
    ui->checkShowInDock->hide();
#endif

    connect(ui->radioLocationAuto, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationSelect, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationCoord, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->radioLocationDisabled, &QRadioButton::clicked, this, &SettingsDialog::locationChangedSlot);
    connect(ui->comboLocation, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsDialog::locationStationChanged);
    connect(ui->comboLocation, &QComboBox::currentTextChanged, this, &SettingsDialog::locationStationTextChanged);
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
    icon.addFile(QStringLiteral(":/Vremenar/Icons/16x16/preferences-system.png"), QSize(16, 16)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(QStringLiteral(":/Vremenar/Icons/24x24/preferences-system.png"), QSize(24, 24)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(QStringLiteral(":/Vremenar/Icons/32x32/preferences-system.png"), QSize(32, 32)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(QStringLiteral(":/Vremenar/Icons/48x48/preferences-system.png"), QSize(48, 48)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    icon.addFile(QStringLiteral(":/Vremenar/Icons/64x64/preferences-system.png"), QSize(64, 64)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    setWindowIcon(icon);
#endif

#ifdef Q_OS_MACOS
    ui->buttons->hide();
#else
    ui->buttonsLayout->setContentsMargins(24, 0, 24, 24); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    connect(ui->buttons, &QDialogButtonBox::accepted, this, &SettingsDialog::close);
#endif

    // Disable notifications if not supported
    if (!notificationsSupported) {
        ui->toolBar->removeAction(ui->actionNotifications);
    }
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

void SettingsDialog::notificationsStatus(bool enabled)
{
    if (!enabled) {
        ui->labelNotificationsStatus->setText(tr("Notifications are currently disabled by the operating system."));

        ui->checkNotifications->setEnabled(false);
        ui->radioAlertsExtreme->setEnabled(false);
        ui->radioAlertsMinor->setEnabled(false);
        ui->radioAlertsModerate->setEnabled(false);
        ui->radioAlertsSevere->setEnabled(false);
        ui->labelWeatherAlerts->setEnabled(false);
    } else {
        ui->labelNotificationsStatus->hide();
    }
}

void SettingsDialog::actionToggled()
{
#if defined(Q_OS_MACOS)
    actionToggledMacOS();
#else
    auto *action = qobject_cast<QAction *>(sender());

    setWindowTitle(action->text());
    if (action == ui->actionGeneral) {
        ui->stackedWidget->setCurrentWidget(ui->pageGeneral);
    } else if (action == ui->actionNotifications) {
        ui->stackedWidget->setCurrentWidget(ui->pageNotifications);
    } else if (action == ui->actionInterface) {
        ui->stackedWidget->setCurrentWidget(ui->pageInterface);
    }
#endif
}

void SettingsDialog::readSettings()
{
    const Settings settings(this);

    ui->checkShowInTray->setChecked(settings.showInTray());
#ifdef Q_OS_MACOS
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
        ui->labelLocationInfo->setEnabled(true);
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
        const QLocale locale;
        ui->lineEditLatitude->setText(locale.toString(settings.locationLatitude()));
        ui->lineEditLongitude->setText(locale.toString(settings.locationLongitude()));
    }

    if (!settings.locationStation().isEmpty()) {
        auto *model = qobject_cast<StationListModel *>(_stationsCompleter->model());
        auto *station = model->find<StationInfo>(settings.locationStation());
        if (station != nullptr) {
            ui->comboLocation->setCurrentIndex(model->indexFromItem(station).row());
        }
    }

    // Notifications
    if (settings.notificationsEnabled()) {
        ui->checkNotifications->setChecked(true);
        ui->radioAlertsExtreme->setEnabled(true);
        ui->radioAlertsMinor->setEnabled(true);
        ui->radioAlertsModerate->setEnabled(true);
        ui->radioAlertsSevere->setEnabled(true);
        ui->labelWeatherAlerts->setEnabled(true);

        switch (settings.notificationsAlertSeverity()) {
        case Weather::MinorSeverity:
            ui->radioAlertsMinor->setChecked(true);
            break;
        case Weather::ModerateSeverity:
            ui->radioAlertsModerate->setChecked(true);
            break;
        case Weather::SevereSeverity:
            ui->radioAlertsSevere->setChecked(true);
            break;
        case Weather::ExtremeSeverity:
            ui->radioAlertsExtreme->setChecked(true);
            break;
        }
    } else {
        ui->checkNotifications->setChecked(false);
        ui->radioAlertsExtreme->setEnabled(false);
        ui->radioAlertsMinor->setEnabled(false);
        ui->radioAlertsModerate->setEnabled(false);
        ui->radioAlertsSevere->setEnabled(false);
        ui->labelWeatherAlerts->setEnabled(false);
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

    emit localeChanged();
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
    ui->labelLocationInfo->setEnabled(settings.locationSource() == Location::Station);
    ui->lineEditLatitude->setEnabled(settings.locationSource() == Location::Coordinate);
    ui->lineEditLongitude->setEnabled(settings.locationSource() == Location::Coordinate);
    if (!ui->radioLocationSelect->isChecked()) {
        ui->comboLocation->lineEdit()->setStyleSheet(QString());
    }

    emit locationChanged();
}

void SettingsDialog::locationCoordinateChanged()
{
    Settings settings(this);
    const QLocale locale;
    if (ui->lineEditLatitude->hasAcceptableInput()) {
        settings.setLocationLatitude(locale.toDouble(ui->lineEditLatitude->text()));
    }
    if (ui->lineEditLongitude->hasAcceptableInput()) {
        settings.setLocationLongitude(locale.toDouble(ui->lineEditLongitude->text()));
    }
    settings.writeSettings();
    emit locationChanged();
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
    Settings settings(this);
    settings.setLocationStation(ui->comboLocation->currentData(StationInfo::IdRole).toString());
    settings.writeSettings();
    emit locationChanged();

    if (settings.locationSource() == Location::Station) {
        ui->comboLocation->lineEdit()->setStyleSheet(QStringLiteral("color: green;"));
    }
}

void SettingsDialog::locationStationTextChanged()
{
    if (!ui->comboLocation->lineEdit()->text().isEmpty() && _stationsCompleter->currentCompletion().isEmpty()) {
        ui->comboLocation->lineEdit()->setStyleSheet(QStringLiteral("color: red;"));
    } else {
        ui->comboLocation->lineEdit()->setStyleSheet(QString());
    }
}

void SettingsDialog::sourceChangedSlot()
{
    emit weatherSourceChanged(ui->comboSource->currentIndex());
}

void SettingsDialog::loadLocales()
{
    const Settings settings(this);

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
    const Settings settings(this);

    disconnect(ui->comboSource, &QComboBox::currentTextChanged, this, &SettingsDialog::sourceChangedSlot);

    ui->comboSource->clear();
    for (const Sources::Country country : {Sources::Slovenia, Sources::Germany}) {
        ui->comboSource->addItem(Sources::countryToLocalizedString(country));
        if (settings.weatherSource() == country) {
            ui->comboSource->setCurrentIndex(ui->comboSource->count() - 1);
        }
    }

    connect(ui->comboSource, &QComboBox::currentTextChanged, this, &SettingsDialog::sourceChangedSlot);
}

void SettingsDialog::notificationsEnabledChangedSlot(bool checked)
{
    Settings settings(this);
    if (settings.notificationsEnabled() != checked) {
        settings.setNotificationsEnabled(checked);
        settings.writeSettings();
        emit notificationsChanged();
    }

    ui->radioAlertsExtreme->setEnabled(checked);
    ui->radioAlertsMinor->setEnabled(checked);
    ui->radioAlertsModerate->setEnabled(checked);
    ui->radioAlertsSevere->setEnabled(checked);
    ui->labelWeatherAlerts->setEnabled(checked);
}

void SettingsDialog::notificationsSeverityChangedSlot()
{
    Settings settings(this);
    if (ui->radioAlertsMinor->isChecked()) {
        settings.setNotificationsAlertSeverity(Weather::MinorSeverity);
    } else if (ui->radioAlertsModerate->isChecked()) {
        settings.setNotificationsAlertSeverity(Weather::ModerateSeverity);
    } else if (ui->radioAlertsSevere->isChecked()) {
        settings.setNotificationsAlertSeverity(Weather::SevereSeverity);
    } else if (ui->radioAlertsExtreme->isChecked()) {
        settings.setNotificationsAlertSeverity(Weather::ExtremeSeverity);
    }
    settings.writeSettings();
    emit notificationsChanged();
}

void SettingsDialog::showInTrayChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setShowInTray(checked);
    settings.writeSettings();

    emit showInTrayChanged(checked);

    ui->checkShowInDock->setEnabled(checked);
    if (!checked) {
        ui->checkShowInDock->setChecked(true);
    }
}

#ifdef Q_OS_MACOS
void SettingsDialog::showInDockChangedSlot(bool checked)
{
    Settings settings(this);
    settings.setShowInDock(checked);
    settings.writeSettings();

    emit showInDockChanged(checked);
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

#include "moc_SettingsDialog.cpp"
