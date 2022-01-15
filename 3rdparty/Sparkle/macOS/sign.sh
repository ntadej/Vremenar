#!/bin/bash

CODE_SIGN_IDENTITY="$1"

if [[ "$CODE_SIGN_IDENTITY" == "" ]]; then
  echo "Code signing identity needs to be set!"
  exit 1
fi

codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime Sparkle.framework/Versions/B/XPCServices/org.sparkle-project.InstallerLauncher.xpc
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime --entitlements Entitlements/org.sparkle-project.Downloader.entitlements Sparkle.framework/Versions/B/XPCServices/org.sparkle-project.Downloader.xpc
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime Sparkle.framework/Versions/B/Autoupdate
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime Sparkle.framework/Versions/B/Updater.app
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime Sparkle.framework
