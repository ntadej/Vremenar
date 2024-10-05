#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/iOS/Assets.xcassets/AppIcon.appiconset"
OUT_LAUNCHER="$DIR/../../resources/iOS/Assets.xcassets/LauncherIcon.imageset"

# shellcheck source=graphics/logo/common.sh
source "$DIR/common.sh"

# iOS logo
apple_sizes_d=(20 20 29 29 38  38 40  40  60  60  64  64  68  76 83.5 1024)
apple_sizes_i=(40 60 58 87 76 114 80 120 120 180 128 192 136 152  167 1024)
apple_scales=( 2x 3x 2x 3x 2x  3x 2x  3x  2x  3x  2x  3x  2x  2x   2x   1x)

for (( i=0; i<${#apple_sizes_i[@]}; i++ ));
do
    $inkscape -o "$OUT/background.png" -w "${apple_sizes_i[$i]}" "$DIR/background_square.svg"
    magick -size "${apple_sizes_i[$i]}x${apple_sizes_i[$i]}" xc:black "$OUT/background_black.png"

    $inkscape -o "$OUT/dark_${apple_sizes_d[$i]}@${apple_scales[$i]}.png" --export-area 80:80:520:520 -w "${apple_sizes_i[$i]}" "$DIR/shape_flat.svg"
    $inkscape -o "$OUT/shape_tinted.png" --export-png-color-mode GrayAlpha_16 --export-area 80:80:520:520 -w "${apple_sizes_i[$i]}" "$DIR/shape_flat.svg"

    echo magick composite -gravity center "$OUT/dark_${apple_sizes_d[$i]}@${apple_scales[$i]}.png" "$OUT/background.png" "$OUT/any_${apple_sizes_d[$i]}@${apple_scales[$i]}.png"
    magick composite -gravity center "$OUT/dark_${apple_sizes_d[$i]}@${apple_scales[$i]}.png" "$OUT/background.png" "$OUT/any_${apple_sizes_d[$i]}@${apple_scales[$i]}.png"

    echo magick composite -gravity center "$OUT/shape_tinted.png" "$OUT/background_black.png" "$OUT/tinted_${apple_sizes_d[$i]}@${apple_scales[$i]}.png"
    magick composite -gravity center "$OUT/shape_tinted.png" "$OUT/background_black.png" "$OUT/tinted_${apple_sizes_d[$i]}@${apple_scales[$i]}.png"

    rm "$OUT/shape_tinted.png" "$OUT/background.png" "$OUT/background_black.png"
done


# Generate JSON
echo "{" > "$OUT/Contents.json"
echo "  \"images\" : [" >> "$OUT/Contents.json"

for (( i=0; i<${#apple_sizes_i[@]}; i++ ));
do
    {
        echo "    {"
        echo "      \"filename\" : \"any_${apple_sizes_d[$i]}@${apple_scales[$i]}.png\","
        echo "      \"idiom\" : \"universal\","
        echo "      \"platform\" : \"ios\","
        echo "      \"scale\" : \"${apple_scales[$i]}\","
        echo "      \"size\" : \"${apple_sizes_d[$i]}x${apple_sizes_d[$i]}\""
        echo "    },"

        echo "    {"
        echo "      \"appearances\" : ["
        echo "        {"
        echo "          \"appearance\" : \"luminosity\","
        echo "          \"value\" : \"dark\""
        echo "        }"
        echo "      ],"
        echo "      \"filename\" : \"dark_${apple_sizes_d[$i]}@${apple_scales[$i]}.png\","
        echo "      \"idiom\" : \"universal\","
        echo "      \"platform\" : \"ios\","
        echo "      \"scale\" : \"${apple_scales[$i]}\","
        echo "      \"size\" : \"${apple_sizes_d[$i]}x${apple_sizes_d[$i]}\""
        echo "    },"

        echo "    {"
        echo "      \"appearances\" : ["
        echo "        {"
        echo "          \"appearance\" : \"luminosity\","
        echo "          \"value\" : \"tinted\""
        echo "        }"
        echo "      ],"
        echo "      \"filename\" : \"tinted_${apple_sizes_d[$i]}@${apple_scales[$i]}.png\","
        echo "      \"idiom\" : \"universal\","
        echo "      \"platform\" : \"ios\","
        echo "      \"scale\" : \"${apple_scales[$i]}\","
        echo "      \"size\" : \"${apple_sizes_d[$i]}x${apple_sizes_d[$i]}\""
        if [ "$i" -eq "$((${#apple_sizes_i[@]}-1))" ]; then
            echo "    }"
        else
            echo "    },"
        fi
    } >> "$OUT/Contents.json"
done

{
    echo "  ],"
    echo "  \"info\" : {"
    echo "    \"author\" : \"xcode\","
    echo "    \"version\" : 1"
    echo "  }"
    echo "}"
} >> "$OUT/Contents.json"

# iOS launcher logo
apple_name=("LauncherIcon" "LauncherIcon@2x" "LauncherIcon@3x")
apple_sizes_d=(120 240 360)

for (( i=0; i<${#apple_name[@]}; i++ ));
do
    $inkscape -o "$OUT_LAUNCHER/${apple_name[$i]}.png" --export-area 80:80:520:520 -w "${apple_sizes_d[$i]}" "$DIR/shape_flat.svg"
done
