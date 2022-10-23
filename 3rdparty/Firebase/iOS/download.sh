#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

FIREBASE_VERSION="9.6.0"

echo "Downloading Firebase"
wget -nv -O "${LOCATION}/firebase-iOS.tar.bz2" "https://github.com/ntadej/firebase-ios-sdk-binaries/releases/download/v${FIREBASE_VERSION}/firebase-iOS.tar.bz2"
tar -C "${LOCATION}" -xvf "${LOCATION}/firebase-iOS.tar.bz2"
