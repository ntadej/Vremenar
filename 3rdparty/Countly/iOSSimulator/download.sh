#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

COUNTLY_VERSION="22.06.1.0"

echo "Downloading Countly"
wget -nv -O "${LOCATION}/Countly-iOSSimulator.tar.bz" "https://github.com/ntadej/countly-sdk-ios/releases/download/${COUNTLY_VERSION}/Countly_${COUNTLY_VERSION}_iOSSimulator.tar.bz2"
tar -C "${LOCATION}" -xvf "${LOCATION}/Countly-iOSSimulator.tar.bz"
