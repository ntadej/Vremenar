#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/tray/components"
OUT="$DIR/tray/modifiers"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define modifiers
modifiers=$(cat "$DIR/modifiers.txt")

for (( i=0; i<${#sizes_tray[@]}; i++ ));
do
    ini="$IN/${folders_tray[$i]}"
    outi="$OUT/${folders_tray[$i]}"
    mkdir -p "$outi"

    IFS=$'\n'
    for modifier in $modifiers;
    do
        IFS=$' '
        read -r -a modifier_list <<< "$modifier"

        name=${modifier_list[0]}${suffixes_tray[$i]}

        echo "$name"

        cp "$ini/${modifier_list[1]}${suffixes_tray[$i]}.png" "$outi/$name.png"

        if [[ ${#modifier_list[@]} -eq 2 ]]; then
            continue
        fi

        for m in "${modifier_list[@]:2}";
        do
            magick composite -gravity center "$ini/${m}${suffixes_tray[$i]}.png" "$outi/$name.png" "$outi/$name.png"
        done
    done
done
