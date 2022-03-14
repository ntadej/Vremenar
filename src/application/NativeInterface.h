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

#ifndef VREMENAR_NATIVEINTERFACE_H_
#define VREMENAR_NATIVEINTERFACE_H_

namespace Vremenar
{

class NotificationsManager;

class NativeInterface
{
public:
    static NativeInterface &getInstance()
    {
        static NativeInterface instance; // Guaranteed to be destroyed.
                                         // Instantiated on first use.
        return instance;
    }

    [[nodiscard]] inline NotificationsManager *notificationsManager() const { return _notificationsManager; }
    void setNotificationsManager(NotificationsManager *manager) { _notificationsManager = manager; };

private:
    NativeInterface() = default;
    ~NativeInterface() = default;

public:
    NativeInterface(NativeInterface const &) = delete;
    void operator=(NativeInterface const &) = delete;

private:
    NotificationsManager *_notificationsManager{};
};

} // namespace Vremenar

#endif // VREMENAR_NATIVEINTERFACE_H_
