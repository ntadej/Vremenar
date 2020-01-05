# Inkscape
if [[ $(uname) = "Darwin" ]]; then
	inkscape="/Applications/Inkscape.app/Contents/MacOS/Inkscape"
else
    inkscape="inkscape"
fi

# Define sizes
sizes=(48 96 144)
sizes_tray_mask=(20 40 60)
suffixes=("" "@2x" "@3x")
