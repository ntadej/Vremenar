#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/macOS
OUT_iconset=$OUT/Vremenar.iconset

# macOS iconset
if [[ ! -d "$OUT_iconset" ]]; then
  mkdir -p "$OUT_iconset"
fi

area="28:28:572:572"

iconset=(16 32 128 256 512)
iconset_retina=(32 64 256 512 1024)
for (( i=0; i<${#iconset[@]}; i++ )); do
  size=${iconset[$i]}x${iconset[$i]}

  inkscape -z --export-png $OUT_iconset/background_${size}.png -a $area -w ${iconset[$i]} $DIR/background_macOS.svg
  inkscape -z --export-png $OUT_iconset/background_${size}@2x.png -a $area -w ${iconset_retina[$i]} $DIR/background_macOS.svg

  inkscape -z --export-png $OUT_iconset/shape_${size}.png -a $area -w ${iconset[$i]} $DIR/shape.svg
  inkscape -z --export-png $OUT_iconset/shape_${size}@2x.png -a $area -w ${iconset_retina[$i]} $DIR/shape.svg

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
