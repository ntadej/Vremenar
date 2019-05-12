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

#ifndef VREMENAR_ABOUTDIALOG_H_
#define VREMENAR_ABOUTDIALOG_H_

#include <memory>

#include <QtWidgets/QDialog>

#include "weather/common/WeatherProviderBase.h"

#include "ui_AboutDialog.h"

namespace Vremenar
{

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(WeatherProviderBase *weatherProvider,
                         QWidget *parent = nullptr);

private:
    std::unique_ptr<Ui::AboutDialog> ui;
};

} // namespace Vremenar

#endif // VREMENAR_ABOUTDIALOG_H_
