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
#ifndef WH_POST_H
#define WH_POST_H

#include <zephyr.h>

#define WH_POST_FS_MOUNT 0x0001
#define WH_POST_FS_VERSION 0x0002
#define WH_POST_VBATT 0x0004
#define WH_POST_THERM 0x0008

// Default POST state is to assume all tests failed
#define WH_POST_DEFAULT 0x0000
// Perfect POST condition state
#define WH_POST_GOOD 0x000F

/**
 * @brief Get the current POST state as a bitmask
 */
extern uint16_t wh_post_state_get();

/**
 * @brief Dump POST status to log
 */
extern void wh_post_dump();

/**
 * @brief Update the current POST state with a failure
 */
extern void wh_post_failed(uint16_t mask);

/**
 * @brief Update the current POST state with a success
 */
extern void wh_post_success(uint16_t mask);

#endif
