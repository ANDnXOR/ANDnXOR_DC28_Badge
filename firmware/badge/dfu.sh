../../provision/cmd.py /dev/ttyACM0 "dfu enter"
sleep 3
dfu-util -D build/zephyr/zephyr.bin -a 0 --dfuse-address 0x8000000:leave
