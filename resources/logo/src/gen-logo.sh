inkscape -z --export-png $PWD/../../Vremenar.png -a 28:28:572:572 -w 64 $PWD/logo.svg
inkscape -z --export-png $PWD/../../VremenarMobile.png -a 80:80:520:520 -w 64 $PWD/logo_mobile.svg

# Desktop logo
sizes=(16 24 32 48 64 128 256)
sizes_retina=(32 48 64 96 128 256 512)
for (( i=1; i<${#sizes[@]}+1; i++ )); do
  inkscape -z --export-png $PWD/../desktop/${sizes[$i]}x${sizes[$i]}/logo.png -a 28:28:572:572 -w ${sizes[$i]} $PWD/logo.svg
  inkscape -z --export-png $PWD/../desktop/${sizes[$i]}x${sizes[$i]}/logo@2x.png -a 28:28:572:572 -w ${sizes_retina[$i]} $PWD/logo.svg
done

# Tray
inkscape -z --export-png $PWD/../desktop/logo_tray.png -a 110:130:490:450 -h 22 $PWD/logo_simple.svg
inkscape -z --export-png $PWD/../desktop/logo_tray@2x.png -a 110:130:490:450 -h 44 $PWD/logo_simple.svg

# Mobile logo
# iOS
apple=("76" "76@2x" "60@2x" "60@3x" "83.5@2x")
apple_sizes=(76 152 120 180 167)
for (( i=1; i<${#apple[@]}+1; i++ ));
do
    inkscape -z --export-png $PWD/../mobile/iOS/AppIcon_${apple[$i]}.png -a 80:80:520:520 -w ${apple_sizes[$i]} $PWD/logo_mobile.svg
done

# Iconset
if [[ ! -d "$PWD/../../Vremenar.iconset" ]]; then
  mkdir -p "$PWD/../../Vremenar.iconset"
fi

iconset=(16 32 128 256 512)
iconset_retina=(32 64 256 512 1024)
for (( i=1; i<${#iconset[@]}+1; i++ )); do
  inkscape -z --export-png $PWD/../../Vremenar.iconset/icon_${iconset[$i]}x${iconset[$i]}.png -a 28:28:572:572 -w ${iconset[$i]} $PWD/logo.svg
  inkscape -z --export-png $PWD/../../Vremenar.iconset/icon_${iconset[$i]}x${iconset[$i]}@2x.png -a 28:28:572:572 -w ${iconset_retina[$i]} $PWD/logo.svg
done
pushd ../../ > /dev/null
iconutil -c icns Vremenar.iconset
rm -r Vremenar.iconset
popd > /dev/null

# Ico
png2ico ../../Vremenar.ico ../desktop/16x16/logo.png ../desktop/32x32/logo.png ../desktop/48x48/logo.png
