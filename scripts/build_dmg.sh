#!/bin/bash

CODE_SIGN_IDENTITY="$4"
PKG_SIGN_IDENTITY="$5"

if [[ "$CODE_SIGN_IDENTITY" != "" ]]; then
  macdeployqt "$1" -qmldir="$3/src/qml/" \
    -appstore-compliant \
    -hardened-runtime \
    -timestamp \
    -codesign="$CODE_SIGN_IDENTITY"
else
  macdeployqt "$1" -qmldir="$3/src/qml/" \
    -appstore-compliant \
    -hardened-runtime
fi

# cleanup
if [[ -f "$1/Contents/PlugIns/geoservices/libqtgeoservices_esri.dylib" ]]; then
  rm "$1/Contents/PlugIns/geoservices/libqtgeoservices_esri.dylib"
fi
if [[ -f "$1/Contents/PlugIns/geoservices/libqtgeoservices_itemsoverlay.dylib" ]]; then
  rm "$1/Contents/PlugIns/geoservices/libqtgeoservices_itemsoverlay.dylib"
fi
if [[ -f "$1/Contents/PlugIns/geoservices/libqtgeoservices_mapbox.dylib" ]]; then
  rm "$1/Contents/PlugIns/geoservices/libqtgeoservices_mapbox.dylib"
fi
if [[ -f "$1/Contents/PlugIns/geoservices/libqtgeoservices_mapboxgl.dylib" ]]; then
  rm "$1/Contents/PlugIns/geoservices/libqtgeoservices_mapboxgl.dylib"
fi
if [[ -f "$1/Contents/PlugIns/geoservices/libqtgeoservices_nokia.dylib" ]]; then
  rm "$1/Contents/PlugIns/geoservices/libqtgeoservices_nokia.dylib"
fi

if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2fusionstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2fusionstyleplugin.dylib"
fi
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2imaginestyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2imaginestyleplugin.dylib"
fi
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2macosstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2macosstyleplugin.dylib"
fi
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2materialstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2materialstyleplugin.dylib"
fi
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2universalstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2universalstyleplugin.dylib"
fi

CONTROLS_DIR="Controls.2"
if [[ -f "$1/Contents/Resources/qml/QtQuick/Controls/libqtquickcontrols2plugin.dylib" ]]; then
  CONTROLS_DIR="Controls"
else
  if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls/" ]]; then
    rm -r "$1/Contents/Resources/qml/QtQuick/Controls/"
  fi
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/designer/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/designer/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Fusion/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Fusion/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Imagine/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Imagine/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Material/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Material/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Universal/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/Universal/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/macOS/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/$CONTROLS_DIR/macOS/"
fi

# Fix the signing
if [[ "$CODE_SIGN_IDENTITY" != "" ]]; then
  echo codesign -s "\"$CODE_SIGN_IDENTITY\"" -f --timestamp -o runtime --entitlements "$2" "$1"
  codesign -s "$CODE_SIGN_IDENTITY" -f --timestamp -o runtime --entitlements "$2" "$1"
fi

if [[ "$PKG_SIGN_IDENTITY" != "" ]]; then
  # build pkg
  productbuild \
    --component "$1" \
    /Applications \
    Vremenar.pkg \
    --sign "$PKG_SIGN_IDENTITY"
else
  # build dmg
  if [[ "$CODE_SIGN_IDENTITY" != "" ]]; then
    create-dmg "$1" --overwrite --identity="$CODE_SIGN_IDENTITY"
    result=$?
  else
    create-dmg "$1" --overwrite
    result=$? 
  fi
fi

if [[ $result -eq 0 || $result -eq 2 ]]; then
  exit 0
else
  exit $result
fi
