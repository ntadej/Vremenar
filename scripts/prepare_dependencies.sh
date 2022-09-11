#!/bin/bash

if [[ -z ${1+x} ]]; then
  echo "Error: Please define the platform!" 1>&2
  exit 1
fi

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && cd .. && pwd)

QT=1
if [[ -z ${Qt5_Dir+x} ]]; then
  echo "Warning: Qt5_Dir not set. Will not modify the Qt installation!"
  QT=0
fi

if [[ "${1}" == "macos" ]] || [[ "${1}" == "macOS" ]]; then
  MAPLIBRE_VERSION="2.0.0-pre.1"
  FIREBASE_VERSION="8.12.1"
  SPARKLE_VERSION="2.0.0"
  COUNTLY_VERSION="21.11.1"

  echo "Downloading for macOS"
  npm install --global create-dmg
  brew install graphicsmagick imagemagick

  # echo
  # echo "MapLibre"
  # if [[ $QT -eq 1 ]]; then
  #   wget -nv -O "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2" "https://github.com/ntadej/qt-geoservices-maplibre/releases/download/v${MAPLIBRE_VERSION}/qt-geoservices-maplibre_${MAPLIBRE_VERSION}_macOS-clang_64.tar.bz2"
  #   tar -C "$Qt5_Dir/" -xvf "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2"
  # else
  #   echo "skipping..."
  # fi

  echo
  echo "Firebase"
  wget -nv -O "${LOCATION}/3rdparty/Firebase/macOS/firebase.tar.bz2" "https://github.com/ntadej/firebase-ios-sdk/releases/download/v${FIREBASE_VERSION}/firebase-macOS.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Firebase/macOS/" -xvf "${LOCATION}/3rdparty/Firebase/macOS/firebase.tar.bz2"

  echo
  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/macOS/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/v${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_macOS.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/macOS/" -xvf "${LOCATION}/3rdparty/Countly/macOS/countly-sdk.tar.bz2"

  echo
  echo "Sparkle"
  wget -nv -O "${LOCATION}/3rdparty/Sparkle/macOS/Sparkle-${SPARKLE_VERSION}.tar.xz" "https://github.com/sparkle-project/Sparkle/releases/download/${SPARKLE_VERSION}/Sparkle-${SPARKLE_VERSION}.tar.xz"
  tar -C "${LOCATION}/3rdparty/Sparkle/macOS/" -xvf "${LOCATION}/3rdparty/Sparkle/macOS/Sparkle-${SPARKLE_VERSION}.tar.xz"

  echo
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "$Qt5_Dir/plugins/platforms/libqcocoa.dylib" "https://github.com/ntadej/qcocoa/releases/download/v${QT_VERSION}.1/libqcocoa.dylib"
    wget -nv -O "$Qt5_Dir/plugins/styles/libqmacstyle.dylib" "https://github.com/ntadej/qmacstyle/releases/download/v${QT_VERSION}.1/libqmacstyle.dylib"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "ios" ]] || [[ "${1}" == "iOS" ]]; then
  MAPLIBRE_VERSION="2.0.0-pre.1"
  FIREBASE_VERSION="8.12.1"
  COUNTLY_VERSION="21.11.1"

  echo "Downloading for iOS"
  brew install ldid

  echo
  echo "MapLibre"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2" "https://github.com/ntadej/qt-geoservices-maplibre/releases/download/v${MAPLIBRE_VERSION}/qt-geoservices-maplibre_${MAPLIBRE_VERSION}_iOS.tar.bz2"
    tar -C "$Qt5_Dir/" -xvf "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2"
  else
    echo "skipping..."
  fi

  echo
  echo "Firebase"
  wget -nv -O "${LOCATION}/3rdparty/Firebase/iOS/firebase.tar.bz2" "https://github.com/ntadej/firebase-ios-sdk/releases/download/v${FIREBASE_VERSION}/firebase-iOS.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Firebase/iOS/" -xvf "${LOCATION}/3rdparty/Firebase/iOS/firebase.tar.bz2"
  wget -nv -O "${LOCATION}/3rdparty/Firebase/iOSSimulator/firebase.tar.bz2" "https://github.com/ntadej/firebase-ios-sdk/releases/download/v${FIREBASE_VERSION}/firebase-iOSSimulator.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Firebase/iOSSimulator/" -xvf "${LOCATION}/3rdparty/Firebase/iOSSimulator/firebase.tar.bz2"

  echo
  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOS/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/v${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_iOS.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOS/" -xvf "${LOCATION}/3rdparty/Countly/iOS/countly-sdk.tar.bz2"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/v${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_iOSSimulator.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOSSimulator/" -xvf "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk.tar.bz2"

  echo
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    # sed -i "" "/BuildSystemType/d" "$Qt5_Dir/mkspecs/macx-xcode/WorkspaceSettings.xcsettings"
    # sed -i "" "/Original/d" "$Qt5_Dir/mkspecs/macx-xcode/WorkspaceSettings.xcsettings"

    # Remove unneeded stuff
    mkdir -p "$Qt5_Dir/backup/lib/cmake/Qt5Location/"
    mkdir -p "$Qt5_Dir/backup/mkspecs/modules/"
    mkdir -p "$Qt5_Dir/backup/plugins/geoservices/"
    mkdir -p "$Qt5_Dir/backup/qml/QtQuick/Controls.2/"
    if [[ -f "$Qt5_Dir/lib/libqmapboxgl.a" ]]; then
      mv "$Qt5_Dir/lib/libqmapboxgl"* "$Qt5_Dir/backup/lib/"
    fi
    if [[ -f "$Qt5_Dir/lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapbox.cmake" ]]; then
      mv "$Qt5_Dir/lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapbox"* "$Qt5_Dir/backup/lib/cmake/Qt5Location/"
    fi
    if [[ -f "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_esri.pri" ]]; then
      mv "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_esri.pri" "$Qt5_Dir/backup/mkspecs/modules/"
    fi
    if [[ -f "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_itemsoverlay.pri" ]]; then
      mv "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_itemsoverlay.pri" "$Qt5_Dir/backup/mkspecs/modules/"
    fi
    if [[ -f "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_mapbox.pri" ]]; then
      mv "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_mapbox"* "$Qt5_Dir/backup/mkspecs/modules/"
    fi
    if [[ -f "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_nokia.pri" ]]; then
      mv "$Qt5_Dir/mkspecs/modules/qt_plugin_qtgeoservices_nokia.pri" "$Qt5_Dir/backup/mkspecs/modules/"
    fi
    if [[ -f "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapbox.a" ]]; then
      mv "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapbox"* "$Qt5_Dir/backup/plugins/geoservices/"
    fi
    if [[ -d "$Qt5_Dir/qml/QtQuick/Controls.2/Fusion" ]]; then
      mv "$Qt5_Dir/qml/QtQuick/Controls.2/Fusion" "$Qt5_Dir/backup/qml/QtQuick/Controls.2/Fusion"
    fi
    if [[ -d "$Qt5_Dir/qml/QtQuick/Controls.2/Imagine" ]]; then
      mv "$Qt5_Dir/qml/QtQuick/Controls.2/Imagine" "$Qt5_Dir/backup/qml/QtQuick/Controls.2/Imagine"
    fi
    if [[ -d "$Qt5_Dir/qml/QtQuick/Controls.2/Material" ]]; then
      mv "$Qt5_Dir/qml/QtQuick/Controls.2/Material" "$Qt5_Dir/backup/qml/QtQuick/Controls.2/Material"
    fi
    if [[ -d "$Qt5_Dir/qml/QtQuick/Controls.2/Universal" ]]; then
      mv "$Qt5_Dir/qml/QtQuick/Controls.2/Universal" "$Qt5_Dir/backup/qml/QtQuick/Controls.2/Universal"
    fi
    if [[ -d "$Qt5_Dir/qml/QtQuick/Controls.2/designer" ]]; then
      mv "$Qt5_Dir/qml/QtQuick/Controls.2/designer" "$Qt5_Dir/backup/qml/QtQuick/Controls.2/designer"
    fi

    wget -nv -O "$Qt5_Dir/plugins/platforms/libqios.tar.bz2" "https://github.com/ntadej/qios/releases/download/v${QT_VERSION}/libqios.tar.bz2"
    tar -C "$Qt5_Dir/plugins/platforms/" -xvf "$Qt5_Dir/plugins/platforms/libqios.tar.bz2"
    rm "$Qt5_Dir/plugins/platforms/libqios.tar.bz2"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "linux" ]] || [[ "${1}" == "Linux" ]]; then
  MAPLIBRE_VERSION="2.0.0-pre.1"

  echo "Downloading for Linux"

  # echo "MapLibre"
  if [[ $QT -eq 1 ]]; then
    # wget -nv -O "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2" "https://github.com/ntadej/qt-geoservices-maplibre/releases/download/v${MAPLIBRE_VERSION}/qt-geoservices-maplibre_${MAPLIBRE_VERSION}_Linux-gcc_64.tar.bz2"
    # tar -C "$Qt5_Dir/" -xvf "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2"
    wget -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.so" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v${QT_VERSION}/libqtgeoservices_mapboxgl_gcc_64.so"
  else
    echo "skipping..."
  fi

  echo
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
  MAPLIBRE_VERSION="2.0.0-pre.1"

  echo "Downloading for Android"

  echo "MapLibre"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2" "https://github.com/ntadej/qt-geoservices-maplibre/releases/download/v${MAPLIBRE_VERSION}/qt-geoservices-maplibre_${MAPLIBRE_VERSION}_Android.tar.bz2"
    tar -C "$Qt5_Dir/" -xvf "${LOCATION}/3rdparty/qt-geoservices-maplibre.tar.bz2"
  else
    echo "skipping..."
  fi

  echo
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    if [[ $OSTYPE == 'darwin'* ]]; then
      sed -i "" -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\' -e '<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_arm64-v8a-android-dependencies.xml"
      sed -i "" -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\' -e '<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_armeabi-v7a-android-dependencies.xml"
      sed -i "" -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\' -e '<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_x86-android-dependencies.xml"
      sed -i "" -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\' -e '<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_x86_64-android-dependencies.xml"
    else
      sed -i -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\n<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_arm64-v8a-android-dependencies.xml"
      sed -i -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\n<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_armeabi-v7a-android-dependencies.xml"
      sed -i -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\n<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_x86-android-dependencies.xml"
      sed -i -e 's/<jar bundling="1" file="jar\/QtAndroidBearer.jar"  \/>/<jar bundling="1" file="jar\/QtAndroidBearer.jar" \/>\n<jar bundling="1" file="jar\/QtAndroidNetwork.jar" \/>/' "$Qt5_Dir/lib/Qt5Network_x86_64-android-dependencies.xml"
    fi
  else
    echo "skipping..."
  fi
else
  echo "Error: Unknown platform!" 1>&2
  exit 2
fi
