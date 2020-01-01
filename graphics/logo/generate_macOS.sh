#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/macOS
OUT_iconset=$OUT/Vremenar.iconset

source $DIR/common.sh

# macOS iconset
if [[ ! -d "$OUT_iconset" ]]; then
  mkdir -p "$OUT_iconset"
fi

area="28:28:572:572"
area_bkg="48:48:552:552"

iconset=(16 32 128 256 512)
iconset_retina=(32 64 256 512 1024)
for (( i=0; i<${#iconset[@]}; i++ )); do
  size=${iconset[$i]}x${iconset[$i]}

  $inkscape -z -o $OUT_iconset/background_${size}.png --export-area=$area_bkg -w ${iconset[$i]} $DIR/background_desktop.svg
  $inkscape -z -o $OUT_iconset/background_${size}@2x.png --export-area=$area_bkg -w ${iconset_retina[$i]} $DIR/background_desktop.svg

  $inkscape -z -o $OUT_iconset/shape_${size}.png --export-area=$area -w ${iconset[$i]} $DIR/shape_flat.svg
  $inkscape -z -o $OUT_iconset/shape_${size}@2x.png --export-area=$area -w ${iconset_retina[$i]} $DIR/shape_flat.svg

  echo magick composite -gravity center $OUT_iconset/shape_${size}.png $OUT_iconset/background_${size}.png $OUT_iconset/icon_${size}.png
  magick composite -gravity center $OUT_iconset/shape_${size}.png $OUT_iconset/background_${size}.png $OUT_iconset/icon_${size}.png

  echo magick composite -gravity center $OUT_iconset/shape_${size}@2x.png $OUT_iconset/background_${size}@2x.png $OUT_iconset/icon_${size}@2x.png
  magick composite -gravity center $OUT_iconset/shape_${size}@2x.png $OUT_iconset/background_${size}@2x.png $OUT_iconset/icon_${size}@2x.png

  rm $OUT_iconset/shape_${size}.png $OUT_iconset/shape_${size}@2x.png $OUT_iconset/background_${size}.png $OUT_iconset/background_${size}@2x.png
done

pushd "$OUT" > /dev/null
iconutil -c icns Vremenar.iconset
rm -r Vremenar.iconset
popd > /dev/null
