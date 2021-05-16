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
  SPARKLE_VERSION="1.26.0"
  COUNTLY_VERSION="20.11.1"

  echo "Downloading for macOS"
  npm install --global create-dmg
  brew install graphicsmagick imagemagick

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
    wget -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.dylib" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v${QT_VERSION}/libqtgeoservices_mapboxgl_clang_64.dylib"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "ios" ]] || [[ "${1}" == "iOS" ]]; then
  COUNTLY_VERSION="20.11.1"

  echo "Downloading for iOS"
  brew install ldid

  echo
  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOS/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/v${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_iOS.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOS/" -xvf "${LOCATION}/3rdparty/Countly/iOS/countly-sdk.tar.bz2"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/v${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_iOSSimulator.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOSSimulator/" -xvf "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk.tar.bz2"

  echo
  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v${QT_VERSION}/libqtgeoservices_mapboxgl_ios.tar.bz2"
    tar -C "$Qt5_Dir/plugins/geoservices/" -xvf "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2"
    rm "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2"

    wget -nv -O "$Qt5_Dir/plugins/platforms/libqios.tar.bz2" "https://github.com/ntadej/qios/releases/download/v${QT_VERSION}/libqios.tar.bz2"
    tar -C "$Qt5_Dir/plugins/platforms/" -xvf "$Qt5_Dir/plugins/platforms/libqios.tar.bz2"
    rm "$Qt5_Dir/plugins/platforms/libqios.tar.bz2"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "linux" ]] || [[ "${1}" == "Linux" ]]; then
  COUNTLY_VERSION="21.05.1"

  echo "Downloading for Linux"

  echo
  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/Linux/countly-sdk.tar.bz2" "https://github.com/ntadej/countly-sdk-cpp/releases/download/${COUNTLY_VERSION}/countly-sdk_${COUNTLY_VERSION}_Linux.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/Linux/" -xvf "${LOCATION}/3rdparty/Countly/Linux/countly-sdk.tar.bz2"

  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.so" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v${QT_VERSION}/libqtgeoservices_mapboxgl_gcc_64.so"

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
    wget -nv -O "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v${QT_VERSION}/libqtgeoservices_mapboxgl_android.tar.bz2"
    tar -C "$Qt5_Dir/plugins/geoservices/" -xvf "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2"
    rm "$Qt5_Dir/plugins/geoservices/libqtgeoservices_mapboxgl.tar.bz2"

    wget -nv -O "$Qt5_Dir/lib/Qt5Network_dependencies_android.tar.bz2" "https://github.com/ntadej/qt-geoservices-mapboxgl/releases/download/v5.15.2/Qt5Network_dependencies_android.tar.bz2"
    tar -C "$Qt5_Dir/lib/" -xvf "$Qt5_Dir/lib/Qt5Network_dependencies_android.tar.bz2"
    rm "$Qt5_Dir/lib/Qt5Network_dependencies_android.tar.bz2"
  else
    echo "skipping..."
  fi
else
  echo "Error: Unknown platform!" 1>&2
  exit 2
fi
