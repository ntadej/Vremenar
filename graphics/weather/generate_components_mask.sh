#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/mask/components"

# shellcheck source=graphics/weather/common.sh
source "$DIR/common.sh"

# Define components
components=$(cat "$DIR/components.txt")

for component in $components;
do
    echo "$component"
    $inkscape -z -C -i "${component}" -j -o "$OUT/${component}.svg" "$DIR/weather-icons-mask.svg"
done
