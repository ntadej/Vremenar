/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_SETTINGSDIALOG_H_
#define VREMENAR_SETTINGSDIALOG_H_

#include <QtWidgets/QActionGroup>
#include <QtWidgets/QMainWindow>

#define MAC_NATIVE_TOOLBAR 1

#if defined(Q_OS_MAC) && MAC_NATIVE_TOOLBAR
#include <QtMacExtras>
#endif

namespace Ui
{
    class SettingsDialog;
}

class SettingsDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

protected:
    void changeEvent(QEvent *e);

signals:
    void localeChanged();
    void showInTrayChanged(bool checked);
#if defined(Q_OS_MAC)
    void showInDockChanged(bool checked);
#endif

private slots:
    void actionToggled();

    void localeChangedSlot();
    void showInTrayChangedSlot(bool checked);
#if defined(Q_OS_MAC)
    void showInDockChangedSlot(bool checked);
#endif
    void rememberPositionChangedSlot(bool checked);
    void rememberSizeChangedSlot(bool checked);

private:
    Ui::SettingsDialog *ui;

    QActionGroup *_group;

    void readSettings();
    void loadLocales();
    QStringList _locales;

#if defined(Q_OS_MAC) && MAC_NATIVE_TOOLBAR
    void initializeMacOS();
    void retranslateMacOS();
    void actionToggledMacOS();

    QMacToolBar *_macToolbar;
    QMacToolBarItem *_macItemGeneral;
    QMacToolBarItem *_macItemInterface;
#endif
};

#endif // VREMENAR_SETTINGSDIALOG_H_
