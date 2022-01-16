#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/iOS/Assets.xcassets/AppIcon.appiconset"
OUT_LAUNCHER="$DIR/../../resources/iOS/Assets.xcassets/LauncherIcon.imageset"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# iOS logo
apple=("iphone-20@2x" "iphone-20@3x" "iphone-29@2x" "iphone-29@3x" "iphone-40@2x" "iphone-40@3x"  "iphone-60@2x" "iphone-60@3x" "ipad-20" "ipad-20@2x" "ipad-29" "ipad-29@2x" "ipad-40" "ipad-40@2x" "ipad-76" "ipad-76@2x" "ipad-83.5@2x" "ios-marketing")
apple_sizes=(40 60 58 87 80 120 120 180 20 40 29 58 40 80 76 152 167 1024)

for (( i=0; i<${#apple[@]}; i++ ));
do
    $inkscape -o "$OUT/background.png" -w "${apple_sizes[$i]}" "$DIR/background_square.svg"

    $inkscape -o "$OUT/shape.png" --export-area 80:80:520:520 -w "${apple_sizes[$i]}" "$DIR/shape_flat.svg"

    echo magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/${apple[$i]}.png"
    magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/${apple[$i]}.png"

    rm "$OUT/shape.png" "$OUT/background.png"
done

# iOS launcher logo
apple=("LauncherIcon" "LauncherIcon@2x" "LauncherIcon@3x")
apple_sizes=(120 240 360)

for (( i=0; i<${#apple[@]}; i++ ));
do
    $inkscape -o "$OUT_LAUNCHER/${apple[$i]}.png" --export-area 80:80:520:520 -w "${apple_sizes[$i]}" "$DIR/shape_flat.svg"
done
