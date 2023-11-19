/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
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

#include <QtGui/QActionGroup>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QCompleter>
#include <QtWidgets/QMainWindow>

#if defined(Q_OS_MACOS)
#include "3rdparty/QMacToolBar.h"
#include "3rdparty/QMacToolBarItem.h"
#endif

#include "weather/Sources.h"

#include "ui_SettingsDialog.h"

namespace Vremenar
{

class StationListModel;

class SettingsDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsDialog(StationListModel *stationsModel,
                            bool notificationsSupported,
                            QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e) final;

public slots:
    void notificationsStatus(bool enabled);

signals:
    void localeChanged();
    void locationChanged();
    void weatherSourceChanged(int source);
    void notificationsChanged();
    void showInTrayChanged(bool checked);
#if defined(Q_OS_MACOS)
    void showInDockChanged(bool checked);
#endif

private slots:
    void actionToggled();

    void localeChangedSlot();
    void locationChangedSlot();
    void locationCoordinateChanged();
    void locationLatitudeValidationChanged();
    void locationLongitudeValidationChanged();
    void locationStationChanged();
    void locationStationTextChanged();
    void sourceChangedSlot();
    void notificationsEnabledChangedSlot(bool checked);
    void notificationsSeverityChangedSlot();
    void showInTrayChangedSlot(bool checked);
#if defined(Q_OS_MACOS)
    void showInDockChangedSlot(bool checked);
#endif
    void rememberPositionChangedSlot(bool checked);
    void rememberSizeChangedSlot(bool checked);

private:
    std::unique_ptr<Ui::SettingsDialog> ui{};

    std::unique_ptr<QActionGroup> _group{};
    std::unique_ptr<QCompleter> _stationsCompleter{};
    std::unique_ptr<QDoubleValidator> _latitudeValidator{};
    std::unique_ptr<QDoubleValidator> _longitudeValidator{};

    void readSettings();
    void loadLocales();
    void loadSources();
    QStringList _locales;

#if defined(Q_OS_MACOS)
    void initializeMacOS(bool notificationsSupported);
    void retranslateMacOS();
    void actionToggledMacOS();

    std::unique_ptr<QMacToolBar> _macToolbar{};
    std::unique_ptr<QMacToolBarItem> _macItemGeneral{};
    std::unique_ptr<QMacToolBarItem> _macItemNotifications{};
    std::unique_ptr<QMacToolBarItem> _macItemInterface{};
#endif
};

} // namespace Vremenar

#endif // VREMENAR_SETTINGSDIALOG_H_
