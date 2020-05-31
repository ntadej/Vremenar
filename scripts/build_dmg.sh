#!/bin/bash

macdeployqt "$1" -qmldir="$2/src/qml/" -appstore-compliant

create-dmg "$1" --overwrite
result=$?
if [[ $result -eq 0 || $result -eq 2 ]]; then
  exit 0
else
  exit $result
fi
