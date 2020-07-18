#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/Web

source $DIR/common.sh

area="110:110:490:490"

$inkscape -o $OUT/logo.png --export-area=$area -w 36 $DIR/shape_flat.svg
$inkscape -o $OUT/logo@2x.png --export-area=$area -w 72 $DIR/shape_flat.svg

area="100:100:500:500"

$inkscape -o $OUT/huge.png --export-area=$area -w 256 $DIR/shape.svg
$inkscape -o $OUT/huge@2x.png --export-area=$area -w 512 $DIR/shape.svg

$inkscape -o $OUT/huge-mobile.png --export-area=$area -w 128 $DIR/shape.svg
$inkscape -o $OUT/huge-mobile@2x.png --export-area=$area -w 256 $DIR/shape.svg

favicon_sizes=(16 32 36)
area="28:28:572:572"

for (( i=0; i<${#favicon_sizes[@]}; i++ ));
do
$inkscape -o $OUT/shape.png --export-area=$area -w ${favicon_sizes[$i]} $DIR/shape.svg
magick composite -gravity center $OUT/shape.png $OUT/favicon_round_${favicon_sizes[$i]}.png $OUT/${favicon_sizes[$i]}.png
rm $OUT/shape.png
done

# MS
ms=("70" "150" "310")
sizes=("70" "150" "310")
length=${#ms[@]}
for (( i=0; i<${length}; i++ ));
do
    $inkscape -o $OUT/mstile_${ms[$i]}.png -w ${sizes[$i]} $DIR/shape.svg
    convert $OUT/mstile_${ms[$i]}.png -gravity center -background transparent -extent ${ms[$i]}x${ms[$i]} $OUT/mstile_${ms[$i]}.png
done
convert $OUT/mstile_150.png -gravity center -background transparent -extent 310x150 $OUT/mstile_310x150.png
