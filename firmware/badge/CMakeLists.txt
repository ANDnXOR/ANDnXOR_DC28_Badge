# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
include($ENV{ZEPHYR_BASE}/cmake/cfb.cmake NO_POLICY_SCOPE)
project(will_hunting)

add_subdirectory(src)

# generate oled font
set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_cfb_font_for_target(app fonts/Px437_IBM_BIOS.ttf ${gen_dir}/cfb_font_ibm.h 8 8 -s 8 --first 0 --last 127)