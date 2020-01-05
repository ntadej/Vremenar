#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/Weather/TrayMask

files=$(find $OUT -iname '*.svg' -and -not -iname '*@*' | sed 's#.*/##' | sed 's#\.svg##' | sort)
ref=$(cat $DIR/db.txt | sort)

diff  <(echo "$ref" ) <(echo "$files")
