#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/Common/ui"

# Inkscape
if [[ $(uname) = "Darwin" ]]; then
	inkscape="/Applications/Inkscape.app/Contents/MacOS/Inkscape"
else
    inkscape="inkscape"
fi

# Spinner
sizes=(32 64 96)
suffixes=("" "@2x" "@3x")

for (( i=0; i<${#sizes[@]}; i++ ));
do
    $inkscape -z -C -o "$OUT/spinner${suffixes[$i]}.png" -w "${sizes[$i]}" -h "${sizes[$i]}" "$DIR/src/load-c.svg"
done
