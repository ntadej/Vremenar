#!/bin/bash

CODE_SIGN_IDENTITY="$1"

if [[ "$CODE_SIGN_IDENTITY" == "" ]]; then
  echo "Code signing identity needs to be set!"
  exit 1
fi

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/Sparkle.framework/Versions/B/XPCServices/Installer.xpc"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime --entitlements "${LOCATION}/Entitlements/Downloader.entitlements" "${LOCATION}/Sparkle.framework/Versions/B/XPCServices/Downloader.xpc"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/Sparkle.framework/Versions/B/Autoupdate"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/Sparkle.framework/Versions/B/Updater.app"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/Sparkle.framework"
