#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN=$DIR/modifiers
INC=$DIR/components
OUT=$DIR/../../resources/Weather/Map

source $DIR/common.sh

# Define clouds and modifiers
clouds=$(cat $DIR/clouds_base.txt)
modifiers=$(cat $DIR/modifiers.txt)

for (( i=0; i<${#sizes[@]}; i++ ));
do
    IFS=$'\n'
    for cloud in $clouds;
    do
        IFS=$'\n'
        for modifier in $modifiers;
        do
            IFS=$' '
            read -a cloud_list <<< $cloud
            read -a modifier_list <<< $modifier

            if [[ "${cloud_list[0]}" == *"_day" ]]; then
                suffix="day"
            else
                suffix="night"
            fi
            cname=${cloud_list[0]}
            cbase=${cname//_${suffix}/}
            mbase=${modifier_list[0]}

            name=${cbase}_${mbase}_${suffix}${suffixes[$i]}

            if [[ "$cbase" == "clear" ]] && [[ "$mbase" != "lightFG" ]]; then
                continue;
            fi

            if [[ "$cbase" == "FG" ]] && [[ "$mbase" == *"FG" ]]; then
                cp $OUT/${cname}${suffixes[$i]}.png $OUT/$name.png
                if [[ "$mbase" == "mod"* ]]; then
                    cp $OUT/$name.png $OUT/${name//mod/}.png
                fi
                continue;
            fi

            echo $name

            if [[ "$mbase" == *"TS"* ]]; then
                cp $INC/storm${suffixes[$i]}.png $OUT/$name.png
                magick composite -gravity center $OUT/${cname}${suffixes[$i]}.png $OUT/$name.png $OUT/$name.png
            else
                cp $OUT/${cname}${suffixes[$i]}.png $OUT/$name.png
            fi

            magick composite -gravity center $IN/${mbase}${suffixes[$i]}.png $OUT/$name.png $OUT/$name.png

            if [[ "$mbase" == "mod"* ]]; then
                cp $OUT/$name.png $OUT/${name//mod/}.png
            fi
        done
    done
done
