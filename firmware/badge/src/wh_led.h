/*****************************************************************************
 * Made with beer and late nights in California.
 *
 * (C) Copyright 2017-2020 AND!XOR LLC (https://andnxor.com/).
 *
 * PROPRIETARY AND CONFIDENTIAL UNTIL AUGUST 11th, 2020 then,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ADDITIONALLY:
 * If you find this source code useful in anyway, use it in another electronic
 * conference badge, or just think it's neat. Consider buying us a beer
 * (or two) and/or a badge (or two). We are just as obsessed with collecting
 * badges as we are in making them.
 *
 * Contributors:
 * 	@andnxor
 * 	@zappbrandnxor
 * 	@hyr0n1
 * 	@bender_andnxor
 * 	@lacosteaef
 *  @f4nci3
 *  @Cr4bf04m
 *****************************************************************************/
#ifndef WH_LED_H
#define WH_LED_H

#include <drivers/led_strip.h>
#include <zephyr.h>

#define WH_LED_COUNT 13
#define WH_LED_MOUTH_INDEX 0
#define WH_LED_MOUTH_MIDDLE_INDEX 4
#define WH_LED_MOUTH_COUNT 7
#define WH_LED_EYEBROW_LEFT_INDEX 7
#define WH_LED_EYEBROW_RIGHT_INDEX 10
#define WH_LED_EYEBROW_COUNT 3

#define WH_LED_COLOR(_R, _G, _B) ((struct led_rgb){0, _R, _G, _B})
#define WH_LED_COLOR_BLACK WH_LED_COLOR(0, 0, 0)
#define WH_LED_COLOR_BLUE WH_LED_COLOR(0, 0, 255)
#define WH_LED_COLOR_GREEN WH_LED_COLOR(0, 255, 0)
#define WH_LED_COLOR_RED WH_LED_COLOR(255, 0, 0)
#define WH_LED_COLOR_MAGENTA WH_LED_COLOR(255, 0, 255)
#define WH_LED_COLOR_WHITE WH_LED_COLOR(255, 255, 255)
#define WH_LED_COLOR_YELLOW WH_LED_COLOR(255, 255, 0)

#define WH_LED_ALL_OFF()              \
  wh_led_set_all(WH_LED_COLOR_BLACK); \
  wh_led_show();

/**
 * @brief Convert HSV values to RGB just like we do every year pinky
 */
extern struct led_rgb wh_led_hsv_to_rgb(float H, float S, float V);

/**
 * @brief Set a single LED color, wh_led_show() must be called to push the data.
 * This function also gamma corrects the color to the LEDs
 * @param index The index of the LED to set
 * @param color The RGB color to set
 */
extern void wh_led_set(uint8_t index, struct led_rgb color);

/**
 * @brief Set all LEDs to a single RGB value
 */
extern void wh_led_set_all(struct led_rgb color);

/**
 * @brief Push LED data to the LEDs all at once
 */
extern void wh_led_show();
#endif