#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/mask/components"
OUT="$DIR/../../resources/Weather/TrayMask"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define clouds
clouds=$(cat "$DIR/clouds_base.txt")

IFS=$'\n'
for cloud in $clouds;
do
    IFS=$' '
    read -r -a cloud_list <<< "$cloud"

    name=${cloud_list[0]}

    echo "$name"

    cp "$IN/${cloud_list[1]}.svg" "$OUT/$name.svg"

    if [[ ! ${#cloud_list[@]} -eq 2 ]]; then
        for c in "${cloud_list[@]:2}";
        do
            "$DIR/combine_svg.py" "$IN/${c}.svg" "$OUT/$name.svg" "$OUT/$name.svg"
        done
    fi

    if [[ "${cloud_list[0]}" == *"day" ]]; then
        cp "$OUT/$name.svg" "$OUT/${name//_day/}.svg"
    fi
done
