#!/bin/bash

CODE_SIGN_IDENTITY="$1"

if [[ "$CODE_SIGN_IDENTITY" == "" ]]; then
  echo "Code signing identity needs to be set!"
  exit 1
fi

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/Countly.framework"
