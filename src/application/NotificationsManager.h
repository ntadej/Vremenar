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

#ifndef VREMENAR_NOTIFICATIONSMANAGER_H_
#define VREMENAR_NOTIFICATIONSMANAGER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Vremenar
{

class StationInfo;

class NotificationsManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationsManager(QString locale,
                                  QObject *parent = nullptr);

    Q_INVOKABLE [[nodiscard]] bool nativeSupported() const;
    Q_INVOKABLE void nativeInitCompleted();
    Q_INVOKABLE void nativeEnabledCheck();
    Q_INVOKABLE void setNotificationsLevel(int level);

signals:
    void nativeEnabledStatus(bool); // NOLINT(readability-named-parameter)

public slots:
    void settingsChanged();
    void localeChanged(const QString &locale);
    void currentStationChanged(Vremenar::StationInfo *station);

private slots:
    void processCoveredAreas(bool enabled);

private:
    void subscribe(const QString &id) const;
    void unsubscribe(const QString &id) const;

    void nativeSubscribe(const QString &id) const;
    void nativeUnsubscribe(const QString &id) const;

    [[nodiscard]] bool nativeSetup();

    bool _waitingForInit{};
    QStringList _coveredAreas;
    QString _currentLocale;
};

} // namespace Vremenar

#endif // VREMENAR_NOTIFICATIONSMANAGER_H_
