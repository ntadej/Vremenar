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

#ifndef VREMENAR_SETTINGSDIALOG_H_
#define VREMENAR_SETTINGSDIALOG_H_

#include <memory>

#include <QtWidgets/QActionGroup>
#include <QtWidgets/QMainWindow>

#if defined(Q_OS_MACOS)
#include <QtMacExtras/QMacToolBar>
#include <QtMacExtras/QMacToolBarItem>
#endif

#include "weather/Sources.h"

#include "ui_SettingsDialog.h"

namespace Vremenar
{

class SettingsDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e) final;

Q_SIGNALS:
    void localeChanged();
    void weatherSourceChanged(int source);
#if defined(Q_OS_MACOS)
    void showInTrayChanged(bool checked);
    void showInDockChanged(bool checked);
#endif

private Q_SLOTS:
    void actionToggled();

    void localeChangedSlot();
    void sourceChangedSlot();
#if defined(Q_OS_MACOS)
    void showInTrayChangedSlot(bool checked);
    void showInDockChangedSlot(bool checked);
#endif
    void rememberPositionChangedSlot(bool checked);
    void rememberSizeChangedSlot(bool checked);

private:
    std::unique_ptr<Ui::SettingsDialog> ui;

    std::unique_ptr<QActionGroup> _group;

    void readSettings();
    void loadLocales();
    void loadSources();
    QStringList _locales;

#if defined(Q_OS_MACOS)
    void initializeMacOS();
    void retranslateMacOS();
    void actionToggledMacOS();

    std::unique_ptr<QMacToolBar> _macToolbar;
    std::unique_ptr<QMacToolBarItem> _macItemGeneral;
    std::unique_ptr<QMacToolBarItem> _macItemInterface;
#endif
};

} // namespace Vremenar

#endif // VREMENAR_SETTINGSDIALOG_H_
