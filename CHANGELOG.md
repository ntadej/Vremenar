# Vremenar Changelog

## 0.5.1 (2022-02-18)

Fixes:
- fix issues with system icons on Windows and macOS
- ensure that menus items for map settings can not be deselected on macOS
- ensure that no map layers are visible at the same time

Future preparation:
- support current stations with no forecast but with fallback

## 0.5.0 (2022-02-12)

New features:
- Windows support
- map slider

Improvements:
- full support for Germany
- improved frameless window handling (macOS and Windows)
- system icons on Windows, macOS and iOS; updated icons on Android
- macOS and iOS store support

## 0.4.0 (2021-12-29)

Improvements:
- add dark streets map style
- add support for UV radiation maps
- improved location settings: location services, manual coordinate, select from list, disabled (desktop only)
- improved transitions between maps of different times
- load supported map types from the API
- do not show navigation bar on Linux

## 0.3.4 (2021-07-19)

Improvements:
- updated maps
- do not allow map navigation outside weather coverage

## 0.3.3 (2021-06-05)

Fixes:
- map selection icon was missing on Android

## 0.3.2 (2021-05-29)

Fixes:
- do not show errors that are not errors
- show backend version for easier error reporting

## 0.3.1 (2021-05-24)

New features:
- Linux support

Fixes:
- better error handling
- proper map controls navigation on TV

## 0.3 (2021-05-02)

Second preview release with new backend and initial DWD support.

New features:
- two map styles, satellite and streets
- better map controls
- light theme
- configurable weather source (ARSO or DWD)
- better TV support

Fixes:
- only show visible map icons for performance gains

Supported platforms:
- macOS
- Android & Android TV (sideload only)
- Amazon Fire TV & Tablets (pending publication)
- iOS (sideload only)

## 0.2 (2020-07-18)

Initial public beta release.

Supported platforms:
- macOS
- Android & Android TV
- iOS (source only)
