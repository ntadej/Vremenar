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

OUT="$DIR/../../resources/Windows/Assets"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# Store logos
sizes_store=(50 63 75 100 200)
labels_store=(100 125 150 200 400)
area="50:50:550:550"

for (( i=0; i<${#sizes_store[@]}; i++ )); do
    $inkscape -o "$OUT/background.png" -w "${sizes_store[$i]}" "$DIR/background_square.svg"
    $inkscape -o "$OUT/shape.png" --export-area "$area" -w "${sizes_store[$i]}" "$DIR/shape.svg"

    magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/StoreLogo.scale-${labels_store[$i]}.png"

    rm "$OUT/shape.png" "$OUT/background.png"
done

# Plated/unplated logos
sizes_plated=(16 24 32 48 256)
area="70:70:530:530"
bkgarea="72:72:952:952"

for (( i=0; i<${#sizes_plated[@]}; i++ )); do
    $inkscape -o "$OUT/background_plated.png" -w "${sizes_plated[$i]}" "$DIR/background_square.svg"
    $inkscape -o "$OUT/background.png" --export-area "$bkgarea" -w "${sizes_plated[$i]}" "$DIR/background_desktop.svg"
    $inkscape -o "$OUT/shape.png" --export-area "$area" -w "${sizes_plated[$i]}" "$DIR/shape.svg"

    magick composite -gravity center "$OUT/shape.png" "$OUT/background_plated.png" "$OUT/VREMENAR-Square44x44Logo.targetsize-${sizes_plated[$i]}.png"
    magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/VREMENAR-Square44x44Logo.targetsize-${sizes_plated[$i]}_altform-unplated.png"

    rm "$OUT/shape.png" "$OUT/background.png" "$OUT/background_plated.png"
done

# Square tiles
sizes_tiles=("44 55 66 88 176" "71 89 107 142 284" "150 188 225 300 600" "310 388 465 620 1240")
ids_tiles=(44 71 150 310)
labels_tiles=(100 125 150 200 400)
areas=("70:70:530:530" "0:0:600:600" "0:0:600:600" "0:0:600:600")

for (( i=0; i<${#ids_tiles[@]}; i++ )); do
    current_sizes=(${sizes_tiles[$i]})
    for (( j=0; j<${#current_sizes[@]}; j++ )); do
        $inkscape -o "$OUT/background.png" -w "${current_sizes[$j]}" "$DIR/background_square.svg"
        $inkscape -o "$OUT/shape.png" --export-area "${areas[$i]}" -w "${current_sizes[$j]}" "$DIR/shape.svg"

        magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/VREMENAR-Square${ids_tiles[$i]}x${ids_tiles[$i]}Logo.scale-${labels_tiles[$j]}.png"

        rm "$OUT/shape.png" "$OUT/background.png"
    done
done

# Wide tiles
sizes_wide_shape=(150 188 225 300 600)
sizes_wide_tiles=(310 388 465 620 1240)
labels_tiles=(100 125 150 200 400)
area="0:0:600:600"

for (( i=0; i<${#sizes_wide_shape[@]}; i++ )); do
    $inkscape -o "$OUT/background.png" -w "${sizes_wide_tiles[$i]}" -h "${sizes_wide_shape[$i]}" "$DIR/background_square.svg"
    $inkscape -o "$OUT/shape.png" --export-area "$area" -w "${sizes_wide_shape[$i]}" "$DIR/shape.svg"

    magick composite -gravity center "$OUT/shape.png" "$OUT/background.png" "$OUT/VREMENAR-Wide310x150Logo.scale-${labels_tiles[$i]}.png"

    rm "$OUT/shape.png" "$OUT/background.png"
done
