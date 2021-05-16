#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/tray/components"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define components
components=$(cat "$DIR/components.txt")

for (( i=0; i<${#sizes_tray[@]}; i++ ));
do
    outi="$OUT/${folders_tray[$i]}"
    mkdir -p "$outi"

    for component in $components;
    do
        echo "$component${suffixes_tray[$i]}"
        $inkscape -z -C -i "${component}" -j -o "$outi/${component}${suffixes_tray[$i]}.png" -w "${sizes_tray[$i]}" -h "${sizes_tray[$i]}" "$DIR/weather-icons-tray.svg"
    done
done
