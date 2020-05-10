#!/bin/bash

if [[ -z ${1+x} ]]; then
  echo "Error: Please define the platform!" 1>&2
  exit 1
fi

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

QT=1
if [[ -z ${Qt5_Dir+x} ]]; then
  echo "Warning: Qt5_Dir not set. Will not modify the Qt installation!"
  QT=0
fi

if [[ "${1}" == "macos" ]] || [[ "${1}" == "macOS" ]]; then
  echo "Downloading for macOS"
  echo "Countly"
  wget -c -nv -O "${LOCATION}/3rdparty/Countly/macOS/countly-sdk_20.04.tar.bz2" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/countly/20.04/clang_x64/countly-sdk_20.04.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/macOS/" -xf "${LOCATION}/3rdparty/Countly/macOS/countly-sdk_20.04.tar.bz2"

  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    wget -c -nv -O "$Qt5_Dir/plugins/platforms/libqcocoa.dylib" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/qcocoa/5.14.0/libqcocoa.dylib"
    wget -c -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.dylib" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/mapbox-gl-native/5.14.2/clang_x64/libqtgeoservices_mapboxgl.dylib"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "linux" ]] || [[ "${1}" == "Linux" ]]; then
  echo "Downloading for Linux"
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    # Fit Qt deployment
    if [[ -f "$Qt5_Dir/plugins/sqldrivers/libqsqlodbc.so" ]]; then
      rm "$Qt5_Dir/plugins/sqldrivers/libqsqlodbc.so"
    fi
    if [[ -f "$Qt5_Dir/plugins/sqldrivers/libqsqlpsql.so" ]]; then
      rm "$Qt5_Dir/plugins/sqldrivers/libqsqlpsql.so"
    fi
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "android" ]] || [[ "${1}" == "Android" ]]; then
  echo "Downloading for Android"
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    # Fix Qt deployment
    sed -i -e 's/qmake_qmake_immediate/qmake_qmake_qm_files/g' \
      "$Qt5_Dir/mkspecs/features/android/android_deployment_settings.prf"
    # Qt patches
    wget -c -nv -O "$Qt5_Dir/plugins/geoservices/libplugins_geoservices_qtgeoservices_mapboxgl_arm64-v8a.so" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/mapbox-gl-native/5.14.2/android/libplugins_geoservices_qtgeoservices_mapboxgl_arm64-v8a.so"
    wget -c -nv -O "$Qt5_Dir/plugins/geoservices/libplugins_geoservices_qtgeoservices_mapboxgl_armeabi-v7a.so" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/mapbox-gl-native/5.14.2/android/libplugins_geoservices_qtgeoservices_mapboxgl_armeabi-v7a.so"
    wget -c -nv -O "$Qt5_Dir/plugins/geoservices/libplugins_geoservices_qtgeoservices_mapboxgl_x86.so" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/mapbox-gl-native/5.14.2/android/libplugins_geoservices_qtgeoservices_mapboxgl_x86.so"
    wget -c -nv -O "$Qt5_Dir/plugins/geoservices/libplugins_geoservices_qtgeoservices_mapboxgl_x86_64.so" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/mapbox-gl-native/5.14.2/android/libplugins_geoservices_qtgeoservices_mapboxgl_x86_64.so"
  else
    echo "skipping..."
  fi
else
  echo "Error: Unknown platform!" 1>&2
  exit 2
fi
