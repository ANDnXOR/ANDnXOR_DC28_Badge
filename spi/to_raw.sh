#!/bin/bash

ffmpeg -i $1 -y -vf "scale=160:128:force_original_aspect_ratio=decrease,pad=160:128:(ow-iw)/2:(oh-ih)/2"  -r 5 -f rawvideo -s 160x128 -pix_fmt rgb565be $2
