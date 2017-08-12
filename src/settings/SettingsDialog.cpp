/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#include "common/LocaleManager.h"
#include "settings/Settings.h"

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    _group = new QActionGroup(this);
    _group->addAction(ui->actionGeneral);
    _group->addAction(ui->actionInterface);

    setWindowTitle(ui->actionGeneral->text());
    setWindowFlags(Qt::Window
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);

#if defined(Q_OS_MAC) && MAC_NATIVE_TOOLBAR
    initializeMacOS();
#else
    connect(ui->actionGeneral, &QAction::toggled, this, &SettingsDialog::actionToggled);
    connect(ui->actionInterface, &QAction::toggled, this, &SettingsDialog::actionToggled);
#endif

    connect(ui->checkShowInTray, &QCheckBox::toggled, this, &SettingsDialog::showInTrayChangedSlot);
    connect(ui->checkRememberPosition, &QCheckBox::toggled, this, &SettingsDialog::rememberPositionChangedSlot);
    connect(ui->checkRememberSize, &QCheckBox::toggled, this, &SettingsDialog::rememberSizeChangedSlot);

#ifdef Q_OS_MAC
    connect(ui->checkShowInDock, &QCheckBox::toggled, this, &SettingsDialog::showInDockChangedSlot);
#else
    ui->checkShowInDock->hide();
#endif

    readSettings();
    loadLocales();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;

    delete _group;
}

void SettingsDialog::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
#if defined(Q_OS_MAC) && MAC_NATIVE_TOOLBAR
        retranslateMacOS();
#endif
        loadLocales();
        break;
    default:
        break;
    }
}

void SettingsDialog::actionToggled()
{
#if defined(Q_OS_MAC) && MAC_NATIVE_TOOLBAR
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
    QScopedPointer<Settings> settings(new Settings(this));

    ui->checkShowInTray->setChecked(settings->showInTray());
#ifdef Q_OS_MAC
    ui->checkShowInDock->setChecked(settings->showInDock());
#endif
    ui->checkRememberPosition->setChecked(settings->rememberPosition());
    ui->checkRememberSize->setChecked(settings->rememberSize());
}

void SettingsDialog::localeChangedSlot()
{
    QScopedPointer<Settings> settings(new Settings(this));
    if (ui->comboLocale->currentIndex() == 0) {
        settings->setLocale("");
    } else {
        settings->setLocale(_locales[ui->comboLocale->currentIndex() - 1]);
    }
    settings->writeSettings();

    emit localeChanged();
}

void SettingsDialog::loadLocales()
{
    QScopedPointer<Settings> settings(new Settings(this));

    disconnect(ui->comboLocale, &QComboBox::currentTextChanged, this, &SettingsDialog::localeChangedSlot);

    _locales = LocaleManager::loadLocales();

    ui->comboLocale->clear();
    ui->comboLocale->addItem(tr("System default"));
    for (const QString &locale : _locales) {
        ui->comboLocale->addItem(QLocale(locale).nativeLanguageName());
        if (settings->locale() == locale) {
            ui->comboLocale->setCurrentIndex(ui->comboLocale->count() - 1);
        }
    }

    connect(ui->comboLocale, &QComboBox::currentTextChanged, this, &SettingsDialog::localeChangedSlot);
}

void SettingsDialog::showInTrayChangedSlot(bool checked)
{
    QScopedPointer<Settings> settings(new Settings(this));
    settings->setShowInTray(checked);
    settings->writeSettings();

    emit showInTrayChanged(checked);

#ifdef Q_OS_MAC
    ui->checkShowInDock->setEnabled(checked);
    if (!checked) {
        ui->checkShowInDock->setChecked(true);
    }
#endif
}

#ifdef Q_OS_MAC
void SettingsDialog::showInDockChangedSlot(bool checked)
{
    QScopedPointer<Settings> settings(new Settings(this));
    settings->setShowInDock(checked);
    settings->writeSettings();

    emit showInDockChanged(checked);
}
#endif

void SettingsDialog::rememberPositionChangedSlot(bool checked)
{
    QScopedPointer<Settings> settings(new Settings(this));
    settings->setRememberPosition(checked);
    settings->writeSettings();
}

void SettingsDialog::rememberSizeChangedSlot(bool checked)
{
    QScopedPointer<Settings> settings(new Settings(this));
    settings->setRememberSize(checked);
    settings->writeSettings();
}
