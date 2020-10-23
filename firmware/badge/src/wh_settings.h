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
#ifndef WH_SETTINGS_H
#define WH_SETTINGS_H

#include <zephyr.h>

#include "autoconf.h"
#include "wh_bender.h"

#define WH_SETTING_KEYBOARD_BACKLIGHT_MAX 20000

typedef struct {
  char name[CONFIG_WH_NAME_MAX_LENGTH + 1];  //+1 for null termination
  uint8_t brightness;
  uint32_t keyboard_led_timeout;
  bool bling_rager;
  bender_data_t bender_state;
  uint16_t unlock;
  uint32_t crc32;
} settings_t;

/**
 * @brief Initialize the settings module
 */
extern void wh_settings_init();

/**
 * @brief Load the settings from persistant storage
 */
extern void wh_settings_load();

/**
 * @brief Get a pointer to the current bender object
 */
extern bender_data_t* wh_settings_bender_ptr_get();

/**
 * @brief Get a pointer to the current settings object
 */
extern settings_t* wh_settings_ptr_get();

/**
 * @brief Factory reset and reboot badge
 */
extern void wh_settings_reset();

/**
 * @brief Save the settings to the filesystem
 */
extern void wh_settings_save();

/**
 * @brief Change the badge name
 */
extern int wh_settings_set_name(char *);

#endif