#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/../../resources/Linux/logo"
OUT="$DIR/../../resources/Windows"

convert \
    "$IN/16x16/vremenar.png" \
    "$IN/24x24/vremenar.png" \
    "$IN/32x32/vremenar.png" \
    "$IN/48x48/vremenar.png" \
    "$IN/64x64/vremenar.png" \
    "$IN/128x128/vremenar.png" \
    "$IN/256x256/vremenar.png" \
    "$OUT/vremenar.ico"
