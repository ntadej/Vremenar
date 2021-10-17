#!/bin/bash

macdeployqt "$1" -qmldir="$2/src/qml/" -appstore-compliant

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
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2materialstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2materialstyleplugin.dylib"
fi
if [[ -f "$1/Contents/PlugIns/quick/libqtquickcontrols2universalstyleplugin.dylib" ]]; then
  rm "$1/Contents/PlugIns/quick/libqtquickcontrols2universalstyleplugin.dylib"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls.2/designer/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls.2/designer/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls.2/Fusion/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls.2/Fusion/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls.2/Imagine/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls.2/Imagine/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls.2/Material/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls.2/Material/"
fi

if [[ -d "$1/Contents/Resources/qml/QtQuick/Controls.2/Universal/" ]]; then
  rm -r "$1/Contents/Resources/qml/QtQuick/Controls.2/Universal/"
fi

# dmg
create-dmg "$1" --overwrite
result=$?
if [[ $result -eq 0 || $result -eq 2 ]]; then
  exit 0
else
  exit $result
fi
