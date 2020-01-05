#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
IN=$DIR/mask/components
OUT=$DIR/mask/modifiers

source $DIR/common.sh

# Define modifiers
modifiers=$(cat $DIR/modifiers.txt)

IFS=$'\n'
for modifier in $modifiers;
do
    IFS=$' '
    read -a modifier_list <<< $modifier

    name=${modifier_list[0]}

    echo $name

    if [[ "${modifier_list[1]}" = "blank" ]]; then
        cp $IN/storm.svg $OUT/$name.svg
    else
        cp $IN/${modifier_list[1]}.svg $OUT/$name.svg
    fi

    if [[ ${#modifier_list[@]} -eq 2 ]]; then
        continue
    fi

    for m in ${modifier_list[@]:2};
    do
        $DIR/combine_svg.py $IN/${m}.svg $OUT/$name.svg $OUT/$name.svg
    done
done
