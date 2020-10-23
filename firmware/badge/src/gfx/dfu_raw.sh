ffmpeg -i dfu.png -y -vf "scale=128:64:force_original_aspect_ratio=decrease,pad=128:64:(ow-iw)/2:(oh-ih)/2"  -r 16 -f rawvideo -s 128x64 -pix_fmt monob dfu.raw

xxd -irc dfu.raw > dfu.h
