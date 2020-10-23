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

#ifndef WH_UI_H
#define WH_UI_H

#include <lvgl.h>

#define WH_UI_KEY_UP 'w'
#define WH_UI_KEY_LEFT 'a'
#define WH_UI_KEY_DOWN 's'
#define WH_UI_KEY_RIGHT 'd'
#define WH_UI_KEY_ENTER '\n'
#define WH_UI_WIDTH 160
#define WH_UI_HEIGHT 128
#define WH_UI_MARGIN 3
#define WH_UI_OLED_WIDTH 128
#define WH_UI_OLED_HEIGHT 64
#define WH_UI_DEBOUNCE_MS 100

/**
 * Signals that the UI can send to the running app
 */
typedef enum {
  wh_ui_signal_exit,      // User requests an exit
  wh_ui_signal_key_ready  // Key ready from user
} wh_ui_signal_t;

/**
 * Results an app can send to the UI when handling the signal
 */
typedef enum {
  wh_ui_signal_result_okay,           // Signal handled appropriately
  wh_ui_signal_result_not_supported,  // Signal not handled because not
                                      // supported
  wh_ui_signal_result_denied  // Signal supported but unable to handle because
                              // some other criteria not met (puzzle not solved
                              // in BENDER for example)
} wh_ui_signal_result_t;

/**
 * @brief Callback function that allows the UI to signal the app based on user
 * interaction.
 * NOTE: The app is not required to handle all signals
 * NOTE: The app should minimize logic / time spent in the callback and handle
 * intensive actions in its own task
 * @param signal The signal code sent by the UI
 * @return Signal result
 */
typedef wh_ui_signal_result_t (*wh_ui_signal_callback_t)(wh_ui_signal_t signal);

/**
 * @brief Clear the UI
 */
extern void wh_ui_clear();

/**
 * @brief Initialize the UI
 */
extern void wh_ui_init();

/**
 * @brief Enable or disable alternate input mode (up / down mapped to prev /
 * next)
 */
extern void wh_ui_input_alt(bool alt);

/**
 * @brief Change the current input group
 */
extern void wh_ui_input_group_set(lv_group_t* group);

/**
 * @brief Enable or disable LVGL
 */
extern void wh_ui_lvgl_enable(bool lvgl);

/**
 * @brief Get the last key pressed by the user as an ASCII code
 */
extern char wh_ui_last_key_get();

/**
 * @brief Set the current signal callback
 */
extern wh_ui_signal_callback_t wh_ui_signal_callback_set(
    wh_ui_signal_callback_t callback);

/**
 * @brief Decode a signal to text
 */
extern char* wh_ui_signal_decode(wh_ui_signal_t signal);

/**
 * @brief Get a pointer to the shared style for window headers
 */
extern lv_style_t* wh_ui_style_header_get();

/**
 * @brief Generic error popup window
 */
extern void wh_ui_window_error(char* error);

#endif