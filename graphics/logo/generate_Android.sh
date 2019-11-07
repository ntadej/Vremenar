#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/Android
OUT_res=$OUT/output/res
OUT_gen=$OUT/generated/res

source $DIR/common.sh

# Android logo
android=("mipmap-mdpi" "mipmap-hdpi" "mipmap-xhdpi" "mipmap-xxhdpi" "mipmap-xxxhdpi")
android_sizes=(48 72 96 144 192)
android_adaptive=(72 108 144 216 288)
android_adaptive_large=(144 216 288 432 576)

area="28:28:572:572"

for (( i=0; i<${#android[@]}; i++ ));
do
    $inkscape -z -o $OUT_gen/${android[$i]}/shape.png --export-area=$area -w ${android_sizes[$i]} $DIR/shape.svg
    $inkscape -z -o $OUT_gen/${android[$i]}/shape_adaptive.png --export-area=$area -w ${android_adaptive[$i]} $DIR/shape.svg
    $inkscape -z -o $OUT_gen/${android[$i]}/shape_adaptive_large.png --export-area=$area -w ${android_adaptive_large[$i]} $DIR/shape.svg

    magick composite -gravity center $OUT_gen/${android[$i]}/shape.png $OUT_gen/${android[$i]}/ic_launcher.png $OUT_res/${android[$i]}/ic_launcher.png
    magick composite -gravity center $OUT_gen/${android[$i]}/shape.png $OUT_gen/${android[$i]}/ic_launcher_round.png $OUT_res/${android[$i]}/ic_launcher_round.png
    magick composite -gravity center $OUT_gen/${android[$i]}/shape_adaptive.png $OUT_gen/${android[$i]}/ic_launcher_foreground.png $OUT_res/${android[$i]}/ic_launcher_foreground.png
    magick composite -gravity center $OUT_gen/${android[$i]}/shape_adaptive_large.png $OUT_gen/${android[$i]}/ic_launcher_foreground.png $OUT_res/${android[$i]}/ic_launcher_foreground_large.png

    rm $OUT_gen/${android[$i]}/shape.png $OUT_gen/${android[$i]}/shape_adaptive.png $OUT_gen/${android[$i]}/shape_adaptive_large.png
done

# For web
$inkscape -z -o $OUT/generated/shape.png --export-area=$area -w 512 $DIR/shape.svg
magick composite -gravity center $OUT/generated/shape.png $OUT/generated/ic_launcher-web.png $OUT/ic_launcher-web.png
rm $OUT/generated/shape.png

# TV
$inkscape -z -o $OUT_gen/background.png -w 320 -h 180 $DIR/background_square.svg
$inkscape -z -o $OUT_gen/shape.png --export-area=80:80:520:520 -w 180 $DIR/shape.svg

echo magick composite -gravity center $OUT_gen/shape.png $OUT_gen/background.png $OUT_res/drawable/tv_banner.png
magick composite -gravity center $OUT_gen/shape.png $OUT_gen/background.png $OUT_res/drawable/tv_banner.png

rm $OUT_gen/shape.png $OUT_gen/background.png