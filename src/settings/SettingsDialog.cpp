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
