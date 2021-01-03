#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/Linux/logo"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# Desktop (Linux) logo
sizes=(16 24 32 48 64 128 256)
sizes_hidpi=(32 48 64 96 128 256 512)

area="28:28:572:572"

for (( i=0; i<${#sizes[@]}; i++ )); do
  CURRENT=$OUT/${sizes[$i]}x${sizes[$i]}

  $inkscape -o "$CURRENT/background.png" -w "${sizes[$i]}" "$DIR/background_desktop.svg"
  $inkscape -o "$CURRENT/background@2x.png" -w "${sizes_hidpi[$i]}" "$DIR/background_desktop.svg"

  $inkscape -o "$CURRENT/shape.png" --export-area "$area" -w "${sizes[$i]}" "$DIR/shape.svg"
  $inkscape -o "$CURRENT/shape@2x.png" --export-area "$area" -w "${sizes_hidpi[$i]}" "$DIR/shape.svg"

  magick composite -gravity center "$CURRENT/shape.png" "$CURRENT/background.png" "$CURRENT/vremenar.png"
  magick composite -gravity center "$CURRENT/shape@2x.png" "$CURRENT/background@2x.png" "$CURRENT/vremenar@2x.png"

  rm "$CURRENT/shape.png" "$CURRENT/shape@2x.png" "$CURRENT/background.png" "$CURRENT/background@2x.png"
done
