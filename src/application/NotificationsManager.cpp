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

#include "application/NotificationsManager.h"

#include "settings/Settings.h"
#include "weather/Weather.h"
#include "weather/containers/StationInfo.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringLiteral>

#include <utility>

namespace Vremenar
{

NotificationsManager::NotificationsManager(QString locale,
                                           QObject *parent)
    : QObject(parent),
      _currentLocale(std::move(locale))
{
    connect(this, &NotificationsManager::nativeEnabledStatus, &NotificationsManager::processCoveredAreas);

    const Settings settings;
    qDebug() << "Notifications:"
             << "Currently subscribed to" << settings.notificationsAlertKeys();
}

void NotificationsManager::nativeInitCompleted()
{
    if (_waitingForInit) {
        _waitingForInit = false;
        settingsChanged();
    }
}

void NotificationsManager::setNotificationsLevel(int level)
{
    Settings settings;
    if (level > Weather::ExtremeSeverity) {
        settings.setNotificationsEnabled(false);
    } else {
        settings.setNotificationsEnabled(true);
        settings.setNotificationsAlertSeverity(static_cast<Weather::AlertSeverity>(level));
    }
    settings.setNotificationsInitialChoice(true);
    settings.writeSettings();

    processCoveredAreas(true);
}

void NotificationsManager::settingsChanged()
{
    processCoveredAreas(true);
}

void NotificationsManager::localeChanged(const QString &locale)
{
    if (_currentLocale != locale) {
        _currentLocale = locale;
        nativeEnabledCheck();
    }
}

void NotificationsManager::currentStationChanged(StationInfo *station)
{
    QStringList alertsAreas;
    if (station != nullptr && !station->alertsArea().isEmpty()) {
        alertsAreas.append(station->alertsArea());
    }

    const Settings settings;
    if (nativeSupported() && settings.notificationsInitialChoice() && settings.notificationsEnabled() && alertsAreas != _coveredAreas) {
        qDebug() << "Notifications:"
                 << "Covered areas changed to:" << alertsAreas;
    }
    _coveredAreas = alertsAreas;

    nativeEnabledCheck();
}

void NotificationsManager::processCoveredAreas(bool enabled)
{
    const Settings settings;

    // build ids
    const QString locale = _currentLocale.split(QStringLiteral("_")).first();
    QStringList existingKeys = settings.notificationsAlertKeys();
    if (enabled && nativeSupported() && settings.notificationsInitialChoice() && settings.notificationsEnabled()) {
        if (!nativeSetup()) {
            qDebug() << "Notifications:"
                     << "initial setup";
            _waitingForInit = true;
            return;
        }

        for (const QString &area : _coveredAreas) {
            auto id = QStringLiteral("%1_%2_%3").arg(locale, Weather::alertSeverityToString(settings.notificationsAlertSeverity()), area);
            if (existingKeys.contains(id)) {
                existingKeys.removeAll(id);
            } else {
                subscribe(id);
            }
        }
    }

    // unsubscribe legacy ids
    for (const QString &id : existingKeys) {
        unsubscribe(id);
    }
}

void NotificationsManager::subscribe(const QString &id) const
{
    Settings settings;
    if (settings.notificationsAlertKeys().contains(id)) {
        return;
    }

    QStringList keys = settings.notificationsAlertKeys();
    keys.append(id);
    settings.setNotificationsAlertKeys(keys);
    settings.writeSettings();

    qDebug() << "Notifications:"
             << "Subscribing to:" << id;

    nativeSubscribe(id);
}

void NotificationsManager::unsubscribe(const QString &id) const
{
    Settings settings;
    if (!settings.notificationsAlertKeys().contains(id)) {
        return;
    }

    QStringList keys = settings.notificationsAlertKeys();
    keys.removeAll(id);
    settings.setNotificationsAlertKeys(keys);
    settings.writeSettings();

    qDebug() << "Notifications:"
             << "Unsubscribing from:" << id;

    nativeUnsubscribe(id);
}

} // namespace Vremenar

// NOLINTBEGIN
#include "moc_NotificationsManager.cpp"
// NOLINTEND
