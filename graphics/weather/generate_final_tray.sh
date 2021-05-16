#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN="$DIR/tray/modifiers"
INC="$DIR/tray/components"
OUT="$DIR/../../resources/Weather/Tray"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define clouds and modifiers
clouds=$(cat "$DIR/clouds_base.txt")
modifiers=$(cat "$DIR/modifiers.txt")

for (( i=0; i<${#sizes_tray[@]}; i++ ));
do
    ini="$IN/${folders_tray[$i]}"
    inci="$INC/${folders_tray[$i]}"
    outi="$OUT/${folders_tray[$i]}"
    mkdir -p "$outi"

    IFS=$'\n'
    for cloud in $clouds;
    do
        IFS=$'\n'
        for modifier in $modifiers;
        do
            IFS=$' '
            read -r -a cloud_list <<< "$cloud"
            read -r -a modifier_list <<< "$modifier"

            if [[ "${cloud_list[0]}" == *"_day" ]]; then
                suffix="day"
            else
                suffix="night"
            fi
            cname=${cloud_list[0]}
            cbase=${cname//_${suffix}/}
            mbase=${modifier_list[0]}

            name=${cbase}_${mbase}_${suffix}${suffixes_tray[$i]}

            if [[ "$cbase" == "clear" ]] && [[ "$mbase" != "lightFG" ]]; then
                continue;
            fi

            if [[ "$cbase" == "FG" ]] && [[ "$mbase" == *"FG" ]]; then
                cp "$outi/${cname}${suffixes_tray[$i]}.png" "$outi/$name.png"
                if [[ "$mbase" == "mod"* ]]; then
                    cp "$outi/$name.png" "$outi/${name//mod/}.png"
                fi
                continue;
            fi

            echo "$name"

            if [[ "$mbase" == *"TS"* ]]; then
                cp "$inci/storm${suffixes_tray[$i]}.png" "$outi/$name.png"
                magick composite -gravity center "$outi/${cname}${suffixes_tray[$i]}.png" "$outi/$name.png" "$outi/$name.png"
            else
                cp "$outi/${cname}${suffixes_tray[$i]}.png" "$outi/$name.png"
            fi

            magick composite -gravity center "$ini/${mbase}${suffixes_tray[$i]}.png" "$outi/$name.png" "$outi/$name.png"

            if [[ "$mbase" == "mod"* ]]; then
                cp "$outi/$name.png" "$outi/${name//mod/}.png"
            fi
        done
    done
done
