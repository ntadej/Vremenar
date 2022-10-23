#!/bin/bash

CODE_SIGN_IDENTITY="$1"

if [[ "$CODE_SIGN_IDENTITY" == "" ]]; then
  echo "Code signing identity needs to be set!"
  exit 1
fi

LOCATION=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/FBLPromises.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/FirebaseCore.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/FirebaseCoreInternal.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/FirebaseInstallations.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/FirebaseMessaging.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/GoogleDataTransport.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/GoogleUtilities.framework"
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime "${LOCATION}/nanopb.framework"
