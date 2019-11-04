#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../../resources/Linux/logo

source $DIR/common.sh

# Desktop (Linux) logo
sizes=(16 24 32 48 64 128 256)
sizes_hidpi=(32 48 64 96 128 256 512)

area="28:28:572:572"
area_bkg="48:48:552:552"

for (( i=0; i<${#sizes[@]}; i++ )); do
  CURRENT=$OUT/${sizes[$i]}x${sizes[$i]}

  $inkscape -z -o $CURRENT/background.png --export-area=$area_bkg -w ${sizes[$i]} $DIR/background_desktop.svg
  $inkscape -z -o $CURRENT/background@2x.png --export-area=$area_bkg -w ${sizes_hidpi[$i]} $DIR/background_desktop.svg

  $inkscape -z -o $CURRENT/shape.png --export-area=$area -w ${sizes[$i]} $DIR/shape.svg
  $inkscape -z -o $CURRENT/shape@2x.png --export-area=$area -w ${sizes_hidpi[$i]} $DIR/shape.svg
  $inkscape -z -o $CURRENT/shape_flat.png --export-area=$area -w ${sizes[$i]} $DIR/shape_flat.svg
  $inkscape -z -o $CURRENT/shape_flat@2x.png --export-area=$area -w ${sizes_hidpi[$i]} $DIR/shape_flat.svg

  magick composite -gravity center $CURRENT/shape.png $CURRENT/background.png $CURRENT/vremenar.png
  magick composite -gravity center $CURRENT/shape@2x.png $CURRENT/background@2x.png $CURRENT/vremenar@2x.png
  magick composite -gravity center $CURRENT/shape_flat.png $CURRENT/background.png $CURRENT/vremenar_flat.png
  magick composite -gravity center $CURRENT/shape_flat@2x.png $CURRENT/background@2x.png $CURRENT/vremenar_flat@2x.png

  rm $CURRENT/shape.png $CURRENT/shape@2x.png $CURRENT/shape_flat.png $CURRENT/shape_flat@2x.png  $CURRENT/background.png $CURRENT/background@2x.png
done
