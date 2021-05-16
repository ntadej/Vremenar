#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

"$DIR/generate_components_tray.sh"
"$DIR/generate_clouds_tray.sh"
"$DIR/generate_modifiers_tray.sh"
"$DIR/generate_final_tray.sh"
"$DIR/validate_tray.sh"
