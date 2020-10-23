#!/bin/sh

# Clear old image
rm -rf image/

# Setup image
mkdir image
mkdir image/BAS
mkdir image/PIX
mkdir image/BLING_BW
mkdir image/USR
mkdir image/USR/BIN

# Copy some files
cp source/VERSION image
cp source/RTFM.MD image
cp source/BINS/DERBY.RAW image/BLING_BW
cp source/BINS/TACOTH image/USR/BIN
cp -R source/BAS image

# Process iamges and videos
./generate_bling.sh
