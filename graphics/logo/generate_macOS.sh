#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/macOS"
OUT_iconset="$OUT/Vremenar.iconset"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# macOS iconset
if [[ ! -d "$OUT_iconset" ]]; then
  mkdir -p "$OUT_iconset"
fi

area="28:28:572:572"

sizes=(16 24 32 48 64 128 256)
sizes_hidpi=(32 48 64 96 128 256 512)

for (( i=0; i<${#sizes[@]}; i++ )); do
  CURRENT=$OUT/logo/${sizes[$i]}x${sizes[$i]}

  $inkscape -o "$CURRENT/background.png" -w "${sizes[$i]}" "$DIR/background_desktop.svg"
  $inkscape -o "$CURRENT/background@2x.png" -w "${sizes_hidpi[$i]}" "$DIR/background_desktop.svg"

  $inkscape -o "$CURRENT/shape.png" --export-area "$area" -w "${sizes[$i]}" "$DIR/shape.svg"
  $inkscape -o "$CURRENT/shape@2x.png" --export-area "$area" -w "${sizes_hidpi[$i]}" "$DIR/shape.svg"

  magick composite -gravity center "$CURRENT/shape.png" "$CURRENT/background.png" "$CURRENT/vremenar.png"
  magick composite -gravity center "$CURRENT/shape@2x.png" "$CURRENT/background@2x.png" "$CURRENT/vremenar@2x.png"

  rm "$CURRENT/shape.png" "$CURRENT/shape@2x.png" "$CURRENT/background.png" "$CURRENT/background@2x.png"
done

iconset=(16 32 128 256 512)
iconset_retina=(32 64 256 512 1024)
for (( i=0; i<${#iconset[@]}; i++ )); do
  size="${iconset[$i]}x${iconset[$i]}"

  $inkscape -o "$OUT_iconset/background_${size}.png" -w "${iconset[$i]}" "$DIR/background_desktop.svg"
  $inkscape -o "$OUT_iconset/background_${size}@2x.png" -w "${iconset_retina[$i]}" "$DIR/background_desktop.svg"

  $inkscape -o "$OUT_iconset/shape_${size}.png" --export-area "$area" -w "${iconset[$i]}" "$DIR/shape.svg"
  $inkscape -o "$OUT_iconset/shape_${size}@2x.png" --export-area "$area" -w "${iconset_retina[$i]}" "$DIR/shape.svg"

  echo magick composite -gravity center "$OUT_iconset/shape_${size}.png" "$OUT_iconset/background_${size}.png" "$OUT_iconset/icon_${size}.png"
  magick composite -gravity center "$OUT_iconset/shape_${size}.png" "$OUT_iconset/background_${size}.png" "$OUT_iconset/icon_${size}.png"

  echo magick composite -gravity center "$OUT_iconset/shape_${size}@2x.png" "$OUT_iconset/background_${size}@2x.png" "$OUT_iconset/icon_${size}@2x.png"
  magick composite -gravity center "$OUT_iconset/shape_${size}@2x.png" "$OUT_iconset/background_${size}@2x.png" "$OUT_iconset/icon_${size}@2x.png"

  rm "$OUT_iconset/shape_${size}.png" "$OUT_iconset/shape_${size}@2x.png" "$OUT_iconset/background_${size}.png" "$OUT_iconset/background_${size}@2x.png"
done

pushd "$OUT" > /dev/null || exit 1
iconutil -c icns Vremenar.iconset
rm -r Vremenar.iconset
popd > /dev/null || exit 1
