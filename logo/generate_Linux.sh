#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
OUT=$DIR/../resources/Linux/logo

# Desktop (Linux) logo
sizes=(16 24 32 48 64 128 256)
sizes_hidpi=(32 48 64 96 128 256 512)

area="48:48:552:552"

for (( i=0; i<${#sizes[@]}; i++ )); do
  CURRENT=$OUT/${sizes[$i]}x${sizes[$i]}

  inkscape -z --export-png $CURRENT/background.png -a $area -w ${sizes[$i]} $DIR/background_desktop.svg
  inkscape -z --export-png $CURRENT/background@2x.png -a $area -w ${sizes_hidpi[$i]} $DIR/background_desktop.svg

  inkscape -z --export-png $CURRENT/shape.png -a $area -w ${sizes[$i]} $DIR/shape.svg
  inkscape -z --export-png $CURRENT/shape@2x.png -a $area -w ${sizes_hidpi[$i]} $DIR/shape.svg

  echo magick composite -gravity center $CURRENT/shape.png $CURRENT/background.png $CURRENT/vremenar.png
  magick composite -gravity center $CURRENT/shape.png $CURRENT/background.png $CURRENT/vremenar.png

  echo magick composite -gravity center $CURRENT/shape@2x.png $CURRENT/background@2x.png $CURRENT/vremenar@2x.png
  magick composite -gravity center $CURRENT/shape@2x.png $CURRENT/background@2x.png $CURRENT/vremenar@2x.png

  rm $CURRENT/shape.png $CURRENT/shape@2x.png $CURRENT/background.png $CURRENT/background@2x.png
done
