#!/bin/bash

CODE_SIGN_IDENTITY="$1"

if [[ "$CODE_SIGN_IDENTITY" == "" ]]; then
  echo "Code signing identity needs to be set!"
  exit 1
fi

codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime FBLPromises.framework
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime FirebaseCore.framework      
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime FirebaseCoreInternal.framework
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime FirebaseInstallations.framework
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime FirebaseMessaging.framework  
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime GoogleDataTransport.framework
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime GoogleUtilities.framework
codesign -f -s "$CODE_SIGN_IDENTITY" -o runtime nanopb.framework
