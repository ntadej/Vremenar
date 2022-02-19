#!/bin/bash

CODE_SIGN_IDENTITY="$3"

# Fix the signing
if [[ "$CODE_SIGN_IDENTITY" != "" ]]; then
  echo codesign -s "\"$CODE_SIGN_IDENTITY\"" -f --timestamp -o runtime --entitlements "$2" "$1"
  codesign -s "$CODE_SIGN_IDENTITY" -f --timestamp -o runtime --entitlements "$2" "$1"
  result=0
fi

if [[ $result -eq 0 || $result -eq 2 ]]; then
  exit 0
else
  exit $result
fi
