#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/components"
OUT="$DIR/modifiers"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define modifiers
modifiers=$(cat "$DIR/modifiers.txt")

for (( i=0; i<${#sizes[@]}; i++ ));
do
    IFS=$'\n'
    for modifier in $modifiers;
    do
        IFS=$' '
        read -r -a modifier_list <<< "$modifier"

        name=${modifier_list[0]}${suffixes[$i]}

        echo "$name"

        cp "$IN/${modifier_list[1]}${suffixes[$i]}.png" "$OUT/$name.png"

        if [[ ${#modifier_list[@]} -eq 2 ]]; then
            continue
        fi

        for m in "${modifier_list[@]:2}";
        do
            magick composite -gravity center "$IN/${m}${suffixes[$i]}.png" "$OUT/$name.png" "$OUT/$name.png"
        done
    done
done
