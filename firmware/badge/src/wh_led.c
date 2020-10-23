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
#include "wh_led.h"

#include <device.h>
#include <drivers/led_strip.h>
#include <logging/log.h>
#include <zephyr.h>

#include "autoconf.h"
#include "devicetree.h"
#include "wh_settings.h"

LOG_MODULE_REGISTER(wh_led, 4);
struct led_rgb m_led_colors[WH_LED_COUNT];

// Thank you Adafruit!
// https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
static const uint8_t GAMMA[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,
    2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,
    4,   5,   5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,
    8,   9,   9,   9,   10,  10,  10,  11,  11,  11,  12,  12,  13,  13,  13,
    14,  14,  15,  15,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,  21,
    21,  22,  22,  23,  24,  24,  25,  25,  26,  27,  27,  28,  29,  29,  30,
    31,  32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  39,  40,  41,  42,
    43,  44,  45,  46,  47,  48,  49,  50,  50,  51,  52,  54,  55,  56,  57,
    58,  59,  60,  61,  62,  63,  64,  66,  67,  68,  69,  70,  72,  73,  74,
    75,  77,  78,  79,  81,  82,  83,  85,  86,  87,  89,  90,  92,  93,  95,
    96,  98,  99,  101, 102, 104, 105, 107, 109, 110, 112, 114, 115, 117, 119,
    120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142, 144, 146,
    148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175, 177,
    180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252,
    255};

/**
 * @brief Convert HSV values to RGB just like we do every year pinky
 */
struct led_rgb wh_led_hsv_to_rgb(float H, float S, float V) {
  float h = H * 6;
  uint8_t i = (uint8_t)h;
  float a = V * (1 - S);
  float b = V * (1 - S * (h - i));
  float c = V * (1 - (S * (1 - (h - i))));
  float rf, gf, bf;

  switch (i) {
    case 0:
      rf = V * 255;
      gf = c * 255;
      bf = a * 255;
      break;
    case 1:
      rf = b * 255;
      gf = V * 255;
      bf = a * 255;
      break;
    case 2:
      rf = a * 255;
      gf = V * 255;
      bf = c * 255;
      break;
    case 3:
      rf = a * 255;
      gf = b * 255;
      bf = V * 255;
      break;
    case 4:
      rf = c * 255;
      gf = a * 255;
      bf = V * 255;
      break;
    case 5:
    default:
      rf = V * 255;
      gf = a * 255;
      bf = b * 255;
      break;
  }

  uint8_t R = rf;
  uint8_t G = gf;
  uint8_t B = bf;

  struct led_rgb RGB = {.r = R, .g = G, .b = B};
  return RGB;
}

/**
 * @brief Push LED data to the LEDs all at once
 */
void wh_led_show() {
  struct device* strip = device_get_binding(DT_INST_0_APA_APA102_LABEL);
  struct led_rgb adjusted_colors[WH_LED_COUNT];

  //Avoid divide by zero
  uint8_t brightness_setting = wh_settings_ptr_get()->brightness;
  if (brightness_setting == 0) {
    brightness_setting = 1;
  }
  uint8_t brightness_divisor = 255 / brightness_setting;

  for (uint8_t i = 0; i < WH_LED_COUNT; i++) {
    adjusted_colors[i].r = GAMMA[m_led_colors[i].r] / brightness_divisor;
    adjusted_colors[i].g = GAMMA[m_led_colors[i].g] / brightness_divisor;
    adjusted_colors[i].b = GAMMA[m_led_colors[i].b] / brightness_divisor;
  }
  led_strip_update_rgb(strip, adjusted_colors, WH_LED_COUNT);
}

/**
 * @brief Set a single LED color, wh_led_show() must be called to push the data.
 * This function also gamma corrects the color to the LEDs
 * @param index The index of the LED to set
 * @param color The RGB color to set
 */
void wh_led_set(uint8_t index, struct led_rgb color) {
  if (index >= WH_LED_COUNT) {
    // Invalid index
    return;
  }
  m_led_colors[index] = color;
}

/**
 * @brief Set all LEDs to a single RGB value
 */
void wh_led_set_all(struct led_rgb color) {
  for (uint8_t i = 0; i < WH_LED_COUNT; i++) {
    wh_led_set(i, color);
  }
}
