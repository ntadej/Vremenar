inkscape -z --export-png $PWD/../../Vremenar.png -a 28:28:572:572 -w 64 $PWD/logo.svg

# Desktop logo
sizes=(16 24 32 48 64 128 256)
sizes_retina=(32 48 64 96 128 256 512)
for (( i=1; i<${#sizes[@]}+1; i++ )); do
  inkscape -z --export-png $PWD/../desktop/${sizes[$i]}x${sizes[$i]}/logo.png -a 28:28:572:572 -w ${sizes[$i]} $PWD/logo.svg
  inkscape -z --export-png $PWD/../desktop/${sizes[$i]}x${sizes[$i]}/logo@2x.png -a 28:28:572:572 -w ${sizes_retina[$i]} $PWD/logo.svg
done

# Tray
inkscape -z --export-png $PWD/../desktop/logo_tray.png -h 22 $PWD/logo_simple.svg
inkscape -z --export-png $PWD/../desktop/logo_tray@2x.png -h 44 $PWD/logo_simple.svg

# Mobile logo
# iOS
apple=("Icon-76" "Icon-76@2x" "Icon-60@2x" "Icon-60@3x" "Icon-83.5@2x" "Icon-Small" "Icon-Small@2x" "Icon-Small@3x" "Icon-Small-40" "Icon-Small-40@2x" "Icon-Small-40@3x")
apple_sizes=(76 152 120 180 167 29 58 87 40 80 120)
for (( i=1; i<${#apple[@]}+1; i++ ));
do
    inkscape -z --export-png $PWD/../../iOS/logo/${apple[$i]}.png -a 80:80:520:520 -w ${apple_sizes[$i]} $PWD/logo_mobile.svg
done

# Iconset
if [[ ! -d "$PWD/../../macOS/Vremenar.iconset" ]]; then
  mkdir -p "$PWD/../../macOS/Vremenar.iconset"
fi

iconset=(16 32 128 256 512)
iconset_retina=(32 64 256 512 1024)
for (( i=1; i<${#iconset[@]}+1; i++ )); do
  inkscape -z --export-png $PWD/../../macOS/Vremenar.iconset/icon_${iconset[$i]}x${iconset[$i]}.png -a 28:28:572:572 -w ${iconset[$i]} $PWD/logo.svg
  inkscape -z --export-png $PWD/../../macOS/Vremenar.iconset/icon_${iconset[$i]}x${iconset[$i]}@2x.png -a 28:28:572:572 -w ${iconset_retina[$i]} $PWD/logo.svg
done
pushd ../../macOS/ > /dev/null
iconutil -c icns Vremenar.iconset
rm -r Vremenar.iconset
popd > /dev/null

# Ico
png2ico ../../Vremenar.ico ../desktop/16x16/logo.png ../desktop/32x32/logo.png ../desktop/48x48/logo.png
