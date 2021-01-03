#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT="$DIR/../../resources/Weather/Map"

files=$(find "$OUT" -iname '*.png' -and -not -iname '*@*' | sed 's#.*/##' | sed 's#\.png##' | sort)
ref=$(sort "$DIR/db.txt")

diff  <(echo "$ref" ) <(echo "$files")
