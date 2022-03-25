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

#ifndef VREMENAR_SERVICES_H_
#define VREMENAR_SERVICES_H_

namespace Vremenar
{

class LocaleManager;
class NotificationsManager;

class Services
{
public:
    static Services &getInstance()
    {
        static Services instance; // Guaranteed to be destroyed.
                                         // Instantiated on first use.
        return instance;
    }

    [[nodiscard]] inline LocaleManager *localeManager() const { return _localeManager; }
    void setLocaleManager(LocaleManager *manager) { _localeManager = manager; }

    [[nodiscard]] inline NotificationsManager *notificationsManager() const { return _notificationsManager; }
    void setNotificationsManager(NotificationsManager *manager) { _notificationsManager = manager; }

private:
    Services() = default;
    ~Services() = default;

public:
    Services(Services const &) = delete;
    void operator=(Services const &) = delete;

private:
    LocaleManager *_localeManager{};
    NotificationsManager *_notificationsManager{};
};

} // namespace Vremenar

#endif // VREMENAR_SERVICES_H_
