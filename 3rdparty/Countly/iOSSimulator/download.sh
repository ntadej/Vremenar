#!/bin/bash

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

COUNTLY_VERSION="23.6.1.0"

echo "Downloading Countly"

set -x

if [[ ! -f "${LOCATION}/Countly-iOSSimulator.tar.bz2" ]]; then
  wget -nv -O "${LOCATION}/Countly-iOSSimulator.tar.bz2" "https://github.com/ntadej/countly-sdk-ios/releases/download/${COUNTLY_VERSION}/Countly_${COUNTLY_VERSION}_iOSSimulator.tar.bz2"
fi
tar -C "${LOCATION}" -xf "${LOCATION}/Countly-iOSSimulator.tar.bz2"
