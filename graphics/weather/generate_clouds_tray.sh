#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/tray/components"
OUT="$DIR/../../resources/Weather/Tray"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define clouds
clouds=$(cat "$DIR/clouds_base.txt")

for (( i=0; i<${#sizes_tray[@]}; i++ ));
do
    ini="$IN/${folders_tray[$i]}"
    outi="$OUT/${folders_tray[$i]}"
    mkdir -p "$outi"

    IFS=$'\n'
    for cloud in $clouds;
    do
        IFS=$' '
        read -r -a cloud_list <<< "$cloud"

        name="${cloud_list[0]}${suffixes_tray[$i]}"

        echo "$name"

        cp "$ini/${cloud_list[1]}${suffixes_tray[$i]}.png" "$outi/$name.png"

        if [[ ! ${#cloud_list[@]} -eq 2 ]]; then
            for c in "${cloud_list[@]:2}";
            do
                magick composite -gravity center "$ini/${c}${suffixes_tray[$i]}.png" "$outi/$name.png" "$outi/$name.png"
            done
        fi

        if [[ "${cloud_list[0]}" == *"day" ]]; then
            cp "$outi/$name.png" "$outi/${name//_day/}.png"
        fi
    done
done
