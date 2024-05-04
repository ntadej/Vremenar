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

#ifndef VREMENAR_ABOUTDIALOG_H_
#define VREMENAR_ABOUTDIALOG_H_

#include "ui_AboutDialog.h"

#include <QtWidgets/QDialog>

#include <memory>

class QWidget;

namespace Vremenar
{

class WeatherProvider;

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(WeatherProvider *weatherProvider,
                         QWidget *parent = nullptr);

private:
    std::unique_ptr<Ui::AboutDialog> ui;
};

} // namespace Vremenar

#endif // VREMENAR_ABOUTDIALOG_H_
