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
#ifndef BBQ10_H
#define BBQ10_H

#include <zephyr.h>

#define KEYCODE_NULL 0
#define KEYCODE_BACKSPACE 8
#define KEYCODE_DEL 127
#define KEYCODE_ENTER 10

// Special Keycodes
#define KEYCODE_ALT 128
#define KEYCODE_MIC 129
#define KEYCODE_SHIFT 130
#define KEYCODE_SPEAKER 131
#define KEYCODE_SYM 132
#define KEYCODE_UP 133
#define KEYCODE_DOWN 134
#define KEYCODE_LEFT 135
#define KEYCODE_RIGHT 136
#define KEYCODE_BACK 137
#define KEYCODE_FN1 138
#define KEYCODE_FN2 139
#define KEYCODE_FN3 140

/**
 * @brief Get a character from the blackberry keyboard, blocking until a
 * character is ready
 * @return The last character typed
 */
extern char bbq10_getc();

/**
 * @brief Set the LED state of the keyboard
 */
extern void bbq10_led_set(bool left, bool right);

/**
 * @brief Returns true if a character is ready from the keyboard
 */
extern bool bbq10_ready();

/**
 * @brief Get the current keyboard state after a debounce
 */
extern uint64_t bbq10_state_get();

#endif