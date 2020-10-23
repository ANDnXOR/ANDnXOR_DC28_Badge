#!/bin/bash
rm -rf zephyrproject
west init --mr v2.2.1 zephyrproject
cd zephyrproject
west update
cd zephyr
source zephyr-env.sh
cd ../..
