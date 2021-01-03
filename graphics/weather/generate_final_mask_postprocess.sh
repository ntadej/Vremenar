#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/Weather/TrayMask"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

for svg in "$OUT"/*.svg;
do
    name=${svg//$OUT\//}
    name=${name//.svg/}
    echo "$name"

    svgo "$OUT/$name.svg"

    for (( i=0; i<${#sizes[@]}; i++ ));
    do
        echo "${suffixes[$i]}"
        $inkscape -z -C -o "$OUT/${name}${suffixes[$i]}.png" -w "${sizes_tray_mask[$i]}" -h "${sizes_tray_mask[$i]}" "$OUT/$name.svg"
    done
done
