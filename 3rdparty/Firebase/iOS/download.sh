#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

FIREBASE_VERSION="10.3.0"

echo "Downloading Firebase"

set -x

if [[ ! -f "${LOCATION}/firebase-iOS.tar.bz2" ]]; then
  wget -nv -O "${LOCATION}/firebase-iOS.tar.bz2" "https://github.com/ntadej/firebase-ios-sdk-binaries/releases/download/v${FIREBASE_VERSION}/firebase-iOS.tar.bz2"
fi
tar -C "${LOCATION}" -xf "${LOCATION}/firebase-iOS.tar.bz2"
