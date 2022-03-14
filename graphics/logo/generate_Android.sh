#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/Android"
OUT_res="$OUT/output/res"
OUT_gen="$OUT/generated/res"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# Android logo
android=("mipmap-mdpi" "mipmap-hdpi" "mipmap-xhdpi" "mipmap-xxhdpi" "mipmap-xxxhdpi")
android_drawable=("drawable-mdpi" "drawable-hdpi" "drawable-xhdpi" "drawable-xxhdpi" "drawable-xxxhdpi")
android_sizes=(48 72 96 144 192)
android_notifications=(24 36 48 72 96)
android_adaptive=(72 108 144 216 288)
android_adaptive_large=(144 216 288 432 576)

area="28:28:572:572"

for (( i=0; i<${#android[@]}; i++ ));
do
    $inkscape -o "$OUT_gen/${android[$i]}/shape.png" --export-area "$area" -w "${android_sizes[$i]}" "$DIR/shape.svg"
    $inkscape -o "$OUT_gen/${android[$i]}/shape_adaptive.png" --export-area "$area" -w "${android_adaptive[$i]}" "$DIR/shape.svg"
    $inkscape -o "$OUT_gen/${android[$i]}/shape_adaptive_large.png" --export-area "$area" -w "${android_adaptive_large[$i]}" "$DIR/shape.svg"
    $inkscape -o "$OUT_res/${android_drawable[$i]}/notification.png" -w "${android_notifications[$i]}" "$DIR/shape_small.svg"

    magick composite -gravity center "$OUT_gen/${android[$i]}/shape.png" "$OUT_gen/${android[$i]}/ic_launcher.png" "$OUT_res/${android[$i]}/ic_launcher.png"
    magick composite -gravity center "$OUT_gen/${android[$i]}/shape.png" "$OUT_gen/${android[$i]}/ic_launcher_round.png" "$OUT_res/${android[$i]}/ic_launcher_round.png"
    magick composite -gravity center "$OUT_gen/${android[$i]}/shape_adaptive.png" "$OUT_gen/${android[$i]}/ic_launcher_foreground.png" "$OUT_res/${android[$i]}/ic_launcher_foreground.png"
    magick composite -gravity center "$OUT_gen/${android[$i]}/shape_adaptive_large.png" "$OUT_gen/${android[$i]}/ic_launcher_foreground.png" "$OUT_res/${android[$i]}/ic_launcher_foreground_large.png"

    rm "$OUT_gen/${android[$i]}/shape.png" "$OUT_gen/${android[$i]}/shape_adaptive.png" "$OUT_gen/${android[$i]}/shape_adaptive_large.png"
done

# For web & Amazon
$inkscape -o "$OUT/generated/shape.png" --export-area "$area" -w 512 "$DIR/shape.svg"
$inkscape -o "$OUT/generated/background.png" -w 512 "$DIR/background_square.svg"
magick composite -gravity center "$OUT/generated/shape.png" "$OUT/generated/ic_launcher-web.png" "$OUT/ic_launcher-web.png"
magick composite -gravity center "$OUT/generated/shape.png" "$OUT/generated/background.png" "$OUT/icon_large.png"
cp "$OUT/ic_launcher-web.png" "$OUT/amazon_large.png"
convert "$OUT_res/mipmap-xxhdpi/ic_launcher.png" -gravity center -crop 114x114+0+0 +repage "$OUT/amazon_small.png"
rm "$OUT/generated/shape.png" "$OUT/generated/background.png"

# TV
$inkscape -o "$OUT_gen/background.png" -w 320 -h 180 "$DIR/background_square.svg"
$inkscape -o "$OUT_gen/background_large.png" -w 1280 -h 720 "$DIR/background_square.svg"
$inkscape -o "$OUT_gen/shape.png" -w 150 "$DIR/shape.svg"
$inkscape -o "$OUT_gen/shape_large.png" -w 600 "$DIR/shape.svg"
$inkscape -o "$OUT_gen/name.png" -w 180 "$DIR/name.svg"
$inkscape -o "$OUT_gen/name_large.png" -w 720 "$DIR/name.svg"

echo magick composite "$OUT_gen/shape.png" "$OUT_gen/background.png" "$OUT_res/drawable/tv_banner.png"
magick composite -gravity West "$OUT_gen/shape.png" "$OUT_gen/background.png" "$OUT_res/drawable-xhdpi/tv_banner.png"
magick composite -gravity East "$OUT_gen/name.png" "$OUT_res/drawable-xhdpi/tv_banner.png" "$OUT_res/drawable-xhdpi/tv_banner.png"

echo magick composite "$OUT_gen/shape_large.png" "$OUT_gen/background_large.png" "$OUT/amazon_tv.png"
magick composite -gravity West "$OUT_gen/shape_large.png" "$OUT_gen/background_large.png" "$OUT/amazon_tv.png"
magick composite -gravity East "$OUT_gen/name_large.png" "$OUT/amazon_tv.png" "$OUT/amazon_tv.png"

rm "$OUT_gen/shape.png" "$OUT_gen/shape_large.png" "$OUT_gen/name.png" "$OUT_gen/name_large.png" "$OUT_gen/background.png" "$OUT_gen/background_large.png"
