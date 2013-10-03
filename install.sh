#!/bin/bash

# This script just makes symlinks for the modules into the arduino library

libs="RGBLamp ComplementaryColors"
arduinoPath="/home/cmol/bin/sketchbook/libraries"

for lib in $libs; do
  if [[ -h "$arduinoPath/$lib" ]]; then
    echo "Link $arduinoPath/$lib exists"
  else
    ln -s "$(pwd)/$lib" "$arduinoPath/$lib"
  fi
done
