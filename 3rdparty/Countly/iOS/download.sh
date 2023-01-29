#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

COUNTLY_VERSION="22.09.0.0"

echo "Downloading Countly"

set -x

wget -nv -O "${LOCATION}/Countly-iOS.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/${COUNTLY_VERSION}/Countly_${COUNTLY_VERSION}_iOS.tar.bz2"
tar -C "${LOCATION}" -xf "${LOCATION}/Countly-iOS.tar.bz2"
