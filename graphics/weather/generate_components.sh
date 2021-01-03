#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/components"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define components
components=$(cat "$DIR/components.txt")

for (( i=0; i<${#sizes[@]}; i++ ));
do
    convert -size "${sizes[$i]}x${sizes[$i]}" xc:transparent "$OUT/blank${suffixes[$i]}.png"

    for component in $components;
    do
        echo "$component${suffixes[$i]}"
        $inkscape -z -C -i "${component}" -j -o "$OUT/${component}${suffixes[$i]}.png" -w "${sizes[$i]}" -h "${sizes[$i]}" "$DIR/weather-icons.svg"
    done
done
