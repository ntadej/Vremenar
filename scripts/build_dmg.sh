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

# dmg
create-dmg "$1" --overwrite
result=$?
if [[ $result -eq 0 || $result -eq 2 ]]; then
  exit 0
else
  exit $result
fi
