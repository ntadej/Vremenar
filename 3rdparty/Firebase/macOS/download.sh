#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

FIREBASE_VERSION="9.6.0"

echo "Downloading Firebase"
wget -nv -O "${LOCATION}/firebase-macOS.tar.bz" "https://github.com/ntadej/firebase-ios-sdk-binaries/releases/download/v${FIREBASE_VERSION}/firebase-macOS.tar.bz2"
tar -C "${LOCATION}" -xvf "${LOCATION}/firebase-macOS.tar.bz"
