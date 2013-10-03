#!/bin/bash

# This script just makes symlinks for the modules into the arduino library

libs="RGBLamp ComplementaryColors"
if [[ -f "$HOME/.arduino/preferences.txt" ]]; then
  arduinoPath="$(cat $HOME/.arduino/preferences.txt | grep sketchbook.path | cut -d "=" -f2)/libraries"
else
  echo "Could not find arduino preferences. Try running arduino first.."
  exit
fi

for lib in $libs; do
  if [[ -h "$arduinoPath/$lib" ]]; then
    echo "Link $arduinoPath/$lib exists"
  else
    ln -s "$(pwd)/$lib" "$arduinoPath/$lib"
  fi
done
