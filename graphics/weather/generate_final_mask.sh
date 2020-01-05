#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN=$DIR/mask/modifiers
INC=$DIR/mask/clouds_base
OUT=$DIR/../../resources/Weather/TrayMask

source $DIR/common.sh

# Define clouds and modifiers
clouds=$(cat $DIR/clouds_base.txt)
modifiers=$(cat $DIR/modifiers.txt)

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

        name=${cbase}_${mbase}_${suffix}

        if [[ "$cbase" == "clear" ]] && [[ "$mbase" != "lightFG" ]]; then
            continue;
        fi

        if [[ "$cbase" == "FG" ]] && [[ "$mbase" == *"FG" ]]; then
            cp $INC/${cname}.svg $OUT/$name.svg
            if [[ "$mbase" == "mod"* ]]; then
                cp $OUT/$name.svg $OUT/${name//mod/}.svg
            fi
            continue;
        fi

        echo $name

        cp $INC/${cname}.svg $OUT/$name.svg

        $DIR/combine_svg.py $IN/${mbase}.svg $OUT/$name.svg $OUT/$name.svg

        if [[ "$mbase" == "mod"* ]]; then
            cp $OUT/$name.svg $OUT/${name//mod/}.svg
        fi
    done
done
