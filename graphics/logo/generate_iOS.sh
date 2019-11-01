#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/iOS/logo

# iOS logo
apple=("Icon-76" "Icon-76@2x" "Icon-60@2x" "Icon-60@3x" "Icon-83.5@2x" "Icon-Small" "Icon-Small@2x" "Icon-Small@3x" "Icon-Small-40" "Icon-Small-40@2x" "Icon-Small-40@3x")
apple_sizes=(76 152 120 180 167 29 58 87 40 80 120)

for (( i=0; i<${#apple[@]}; i++ ));
do
    inkscape -z --export-png $OUT/background.png -w ${apple_sizes[$i]} $DIR/background_square.svg

    inkscape -z --export-png $OUT/shape.png -a 80:80:520:520 -w ${apple_sizes[$i]} $DIR/shape.svg

    echo magick composite -gravity center $OUT/shape.png $OUT/background.png $OUT/${apple[$i]}.png
    magick composite -gravity center $OUT/shape.png $OUT/background.png $OUT/${apple[$i]}.png

    rm $OUT/shape.png $OUT/background.png
done
