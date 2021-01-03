#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

"$DIR/generate_components.sh"
"$DIR/generate_clouds.sh"
"$DIR/generate_modifiers.sh"
"$DIR/generate_final.sh"
"$DIR/validate.sh"
