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
  echo "Downloading for macOS"
  npm install --global create-dmg
  brew install graphicsmagick imagemagick

  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/macOS/countly-sdk_20.04.tar.bz2" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/countly/20.04/clang_x64/countly-sdk_20.04.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/macOS/" -xf "${LOCATION}/3rdparty/Countly/macOS/countly-sdk_20.04.tar.bz2"

  echo "Sparkle"
  wget -nv -O "${LOCATION}/3rdparty/Sparkle/macOS/Sparkle-1.23.0.tar.xz" "https://github.com/sparkle-project/Sparkle/releases/download/1.23.0/Sparkle-1.23.0.tar.xz"
  tar -C "${LOCATION}/3rdparty/Sparkle/macOS/" -xf "${LOCATION}/3rdparty/Sparkle/macOS/Sparkle-1.23.0.tar.xz"

  echo "Qt Patches"
  if [[ $QT -eq 1 ]]; then
    wget -nv -O "$Qt5_Dir/plugins/platforms/libqcocoa.dylib" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/qcocoa/${QT_VERSION}/libqcocoa.dylib"
  else
    echo "skipping..."
  fi
elif [[ "${1}" == "ios" ]] || [[ "${1}" == "iOS" ]]; then
  echo "Downloading for iOS"
  echo "Countly"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOS/countly-sdk_20.04.tar.bz2" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/countly/20.04/ios/countly-sdk_20.04.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOS/" -xf "${LOCATION}/3rdparty/Countly/iOS/countly-sdk_20.04.tar.bz2"
  wget -nv -O "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk_20.04.tar.bz2" "https://dl.bintray.com/tano-si/Vremenar-Dependencies/countly/20.04/iossimulator/countly-sdk_20.04.tar.bz2"
  tar -C "${LOCATION}/3rdparty/Countly/iOSSimulator/" -xf "${LOCATION}/3rdparty/Countly/iOSSimulator/countly-sdk_20.04.tar.bz2"
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
  echo "Nothing to be done!"
else
  echo "Error: Unknown platform!" 1>&2
  exit 2
fi
