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

#include "weather/arso/models/ARSOMapLegendModel.h"

namespace Vremenar
{

// clazy:excludeall=qcolor-from-literal

ARSO::MapLegendModel::MapLegendModel(QObject *parent)
    : MapLegendModelBase(parent)
{
    // Precipitation
    emplace(Weather::PrecipitationMap, QString(), QColor("transparent"), true);
    emplace(Weather::PrecipitationMap, QStringLiteral("0"), QColor("transparent"));
    emplace(Weather::PrecipitationMap, QStringLiteral("15"), QColor("#3e67ff"));
    emplace(Weather::PrecipitationMap, QStringLiteral("18"), QColor("#3797ff"));
    emplace(Weather::PrecipitationMap, QStringLiteral("21"), QColor("#30c1f6"));
    emplace(Weather::PrecipitationMap, QStringLiteral("24"), QColor("#31e7fc"));
    emplace(Weather::PrecipitationMap, QStringLiteral("27"), QColor("#33d397"));
    emplace(Weather::PrecipitationMap, QStringLiteral("30"), QColor("#2fef28"));
    emplace(Weather::PrecipitationMap, QStringLiteral("33"), QColor("#8bfa36"));
    emplace(Weather::PrecipitationMap, QStringLiteral("36"), QColor("#c8fa33"));
    emplace(Weather::PrecipitationMap, QStringLiteral("39"), QColor("#f6fb2a"));
    emplace(Weather::PrecipitationMap, QStringLiteral("42"), QColor("#fed430"));
    emplace(Weather::PrecipitationMap, QStringLiteral("45"), QColor("#ff9a2c"));
    emplace(Weather::PrecipitationMap, QStringLiteral("48"), QColor("#fe6637"));
    emplace(Weather::PrecipitationMap, QStringLiteral("51"), QColor("#d42e38"));
    emplace(Weather::PrecipitationMap, QStringLiteral("54"), QColor("#b22923"));
    emplace(Weather::PrecipitationMap, QStringLiteral("57"), QColor("#d436d7"));
    emplace(Weather::PrecipitationMap, QStringLiteral("dBZ"), QColor("transparent"), true);

    // Wind
    emplace(Weather::WindSpeedMap, QString(), QColor("transparent"), true);
    emplace(Weather::WindSpeedMap, QStringLiteral("0"), QColor("transparent"));
    emplace(Weather::WindSpeedMap, QStringLiteral("10"), QColor("#09609680"));
    emplace(Weather::WindSpeedMap, QStringLiteral("20"), QColor("#096"));
    emplace(Weather::WindSpeedMap, QStringLiteral("30"), QColor("#96c"));
    emplace(Weather::WindSpeedMap, QStringLiteral("40"), QColor("#e54cff"));
    emplace(Weather::WindSpeedMap, QStringLiteral("50"), QColor("#f09"));
    emplace(Weather::WindSpeedMap, QStringLiteral("60"), QColor("#e51919"));
    emplace(Weather::WindSpeedMap, QStringLiteral("70"), QColor("#933"));
    emplace(Weather::WindSpeedMap, QStringLiteral("80"), QColor("#4c3333"));
    emplace(Weather::WindSpeedMap, QStringLiteral("90"), QColor("#630"));
    emplace(Weather::WindSpeedMap, QStringLiteral("100"), QColor("#963"));
    emplace(Weather::WindSpeedMap, QStringLiteral("110"), QColor("#b29966"));
    emplace(Weather::WindSpeedMap, QStringLiteral("km/h"), QColor("transparent"), true);

    // Temperature
    emplace(Weather::TemperatureMap, QString(), QColor("transparent"), true);
    emplace(Weather::TemperatureMap, QStringLiteral("-22"), QColor("#fff"));
    emplace(Weather::TemperatureMap, QStringLiteral("-20"), QColor("#e1e1e1"));
    emplace(Weather::TemperatureMap, QStringLiteral("-18"), QColor("#bebebe"));
    emplace(Weather::TemperatureMap, QStringLiteral("-16"), QColor("#828282"));
    emplace(Weather::TemperatureMap, QStringLiteral("-14"), QColor("#565474"));
    emplace(Weather::TemperatureMap, QStringLiteral("-12"), QColor("#59447f"));
    emplace(Weather::TemperatureMap, QStringLiteral("-10"), QColor("#47007f"));
    emplace(Weather::TemperatureMap, QStringLiteral("-8"), QColor("#32007f"));
    emplace(Weather::TemperatureMap, QStringLiteral("-6"), QColor("#0000ac"));
    emplace(Weather::TemperatureMap, QStringLiteral("-4"), QColor("#0000f0"));
    emplace(Weather::TemperatureMap, QStringLiteral("-2"), QColor("#2059e7"));
    emplace(Weather::TemperatureMap, QStringLiteral("0"), QColor("#007eff"));
    emplace(Weather::TemperatureMap, QStringLiteral("2"), QColor("#00beff"));
    emplace(Weather::TemperatureMap, QStringLiteral("4"), QColor("#aff"));
    emplace(Weather::TemperatureMap, QStringLiteral("6"), QColor("#01f7c6"));
    emplace(Weather::TemperatureMap, QStringLiteral("8"), QColor("#18d78c"));
    emplace(Weather::TemperatureMap, QStringLiteral("10"), QColor("#00aa64"));
    emplace(Weather::TemperatureMap, QStringLiteral("12"), QColor("#2baa2b"));
    emplace(Weather::TemperatureMap, QStringLiteral("14"), QColor("#2bc82b"));
    emplace(Weather::TemperatureMap, QStringLiteral("16"), QColor("#01ff00"));
    emplace(Weather::TemperatureMap, QStringLiteral("18"), QColor("#cf0"));
    emplace(Weather::TemperatureMap, QStringLiteral("20"), QColor("#ff0"));
    emplace(Weather::TemperatureMap, QStringLiteral("22"), QColor("#eded7e"));
    emplace(Weather::TemperatureMap, QStringLiteral("24"), QColor("#e4cc66"));
    emplace(Weather::TemperatureMap, QStringLiteral("26"), QColor("#dcae49"));
    emplace(Weather::TemperatureMap, QStringLiteral("28"), QColor("#fa0"));
    emplace(Weather::TemperatureMap, QStringLiteral("30"), QColor("#f50"));
    emplace(Weather::TemperatureMap, QStringLiteral("32"), QColor("red"));
    emplace(Weather::TemperatureMap, QStringLiteral("34"), QColor("#c80000"));
    emplace(Weather::TemperatureMap, QStringLiteral("36"), QColor("#780000"));
    emplace(Weather::TemperatureMap, QStringLiteral("38"), QColor("#640000"));
    emplace(Weather::TemperatureMap, QStringLiteral("40"), QColor("#500000"));
    emplace(Weather::TemperatureMap, QStringLiteral("°C"), QColor("transparent"), true);

    // Hail
    emplace(Weather::HailProbabilityMap, QString(), QColor("transparent"), true);
    emplace(Weather::HailProbabilityMap, QString(), QColor("transparent"));
    emplace(Weather::HailProbabilityMap, tr("low"), QColor("#fae100"));
    emplace(Weather::HailProbabilityMap, tr("moderate"), QColor("#fa7d00"));
    emplace(Weather::HailProbabilityMap, tr("large"), QColor("#fa0000"));
    emplace(Weather::HailProbabilityMap, tr("probability"), QColor("transparent"), true);
}

} // namespace Vremenar
