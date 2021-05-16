# Inkscape
if [[ $(uname) = "Darwin" ]]; then
	inkscape="/Applications/Inkscape.app/Contents/MacOS/Inkscape"
else
    inkscape="inkscape"
fi

# Define sizes
sizes=(48 96 144)
sizes_tray=(16 24 32 32 48 64 48 72 96)
sizes_tray_mask=(20 40 60)
suffixes=("" "@2x" "@3x")
suffixes_tray=("" "" "" "@2x" "@2x" "@2x" "@3x" "@3x" "@3x")
folders_tray=(16 24 32 16 24 32 16 24 32)
