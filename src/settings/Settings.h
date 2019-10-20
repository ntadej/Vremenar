/*
* Vremenar
* Copyright (C) 2019 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

#ifndef VREMENAR_SETTINGS_H_
#define VREMENAR_SETTINGS_H_

#include <QtCore/QSettings>

namespace Vremenar
{

class Settings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(bool rememberPosition READ rememberPosition CONSTANT)
    Q_PROPERTY(bool rememberSize READ rememberSize CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)
    Q_PROPERTY(int posX READ posX CONSTANT)
    Q_PROPERTY(int posY READ posY CONSTANT)

public:
    explicit Settings(QObject *parent = nullptr);

    Q_INVOKABLE void readSettings();
    void writeSettings();

    Q_INVOKABLE QVariant defaultValue(const QString &key) const;

    // Locale
    inline const QString &locale() const { return _locale; }
    inline void setLocale(const QString &s) { _locale = s; }
    static const QString KEY_LOCALE;
    static const QString DEFAULT_LOCALE;

    // GUI
    inline bool showInTray() const { return _showInTray; }
    inline void setShowInTray(bool b) { _showInTray = b; }
    static const QString KEY_SHOW_IN_TRAY;
    static const bool DEFAULT_SHOW_IN_TRAY;

#if defined(Q_OS_MACOS)
    // macOS special
    inline bool showInDock() const { return _showInDock; }
    inline void setShowInDock(bool b) { _showInDock = b; }
    static const QString KEY_SHOW_IN_DOCK;
    static const bool DEFAULT_SHOW_IN_DOCK;
#endif

    // GUI - session
    inline bool rememberPosition() const { return _rememberPosition; }
    inline void setRememberPosition(bool b) { _rememberPosition = b; }
    static const QString KEY_REMEMBER_POSITION;
    static const bool DEFAULT_REMEMBER_POSITION;

    inline bool rememberSize() const { return _rememberSize; }
    inline void setRememberSize(bool b) { _rememberSize = b; }
    static const QString KEY_REMEMBER_SIZE;
    static const bool DEFAULT_REMEMBER_SIZE;

    inline int width() const { return _width; }
    inline void setWidth(int i) { _width = i; }
    static const QString KEY_WIDTH;
    static const int DEFAULT_WIDTH;

    inline int height() const { return _height; }
    inline void setHeight(int i) { _height = i; }
    static const QString KEY_HEIGHT;
    static const int DEFAULT_HEIGHT;

    inline int posX() const { return _posX; }
    inline void setPosX(int i) { _posX = i; }
    static const QString KEY_POS_X;
    static const int DEFAULT_POS_X;

    inline int posY() const { return _posY; }
    inline void setPosY(int i) { _posY = i; }
    static const QString KEY_POS_Y;
    static const int DEFAULT_POS_Y;

Q_SIGNALS:
    void settingsReloaded();

private:
    QVariantMap _map;

    // Locale
    QString _locale;

    // GUI
    bool _showInTray;
#if defined(Q_OS_MACOS)
    bool _showInDock;
#endif

    // GUI - session
    bool _rememberPosition;
    bool _rememberSize;
    int _width;
    int _height;
    int _posX;
    int _posY;
};

} // namespace Vremenar

#endif // VREMENAR_SETTINGS_H_
