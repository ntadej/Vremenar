#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/components"
OUT="$DIR/../../resources/Weather/Map"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define clouds
clouds=$(cat "$DIR/clouds_base.txt")

for (( i=0; i<${#sizes[@]}; i++ ));
do
    IFS=$'\n'
    for cloud in $clouds;
    do
        IFS=$' '
        read -r -a cloud_list <<< "$cloud"

        name="${cloud_list[0]}${suffixes[$i]}"

        echo "$name"

        cp "$IN/${cloud_list[1]}${suffixes[$i]}.png" "$OUT/$name.png"

        if [[ ! ${#cloud_list[@]} -eq 2 ]]; then
            for c in "${cloud_list[@]:2}";
            do
                magick composite -gravity center "$IN/${c}${suffixes[$i]}.png" "$OUT/$name.png" "$OUT/$name.png"
            done
        fi

        if [[ "${cloud_list[0]}" == *"day" ]]; then
            cp "$OUT/$name.png" "$OUT/${name//_day/}.png"
        fi
    done
done
