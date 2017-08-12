/*
* Vremenar
* Copyright (C) 2017 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*/

#ifndef VREMENAR_SETTINGS_H_
#define VREMENAR_SETTINGS_H_

#include <QtCore/QSettings>

class Settings : public QSettings
{
public:
    Settings(QObject *parent = 0);
    ~Settings();

    void readSettings();
    void writeSettings();

    QVariant defaultValue(const QString &key) const;

    // Locale
    inline QString locale() const { return _locale; }
    inline void setLocale(const QString &s) { _locale = s; }
    static const QString KEY_LOCALE;
    static const QString DEFAULT_LOCALE;

    // GUI - session
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

private:
    QVariantMap _map;

    // Locale
    QString _locale;

    // GUI - session
    int _width;
    int _height;
    int _posX;
    int _posY;
};

#endif // VREMENAR_SETTINGS_H_
