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
#ifndef WH_UTIL_H
#define WH_UTIL_H

/**
 * @brief Get the unique badge id for this badge
 */
extern uint32_t wh_util_badge_id_get();

/**
 * @brief Set the badge ID
 */
extern void wh_util_badge_id_set(uint16_t new_badge_id);

/**
 * @brief Jump to the STM32F412 bootloader
 * Adapted from
 * https://stm32f4-discovery.net/2017/04/tutorial-jump-system-memory-software-stm32/
 */
extern void wh_util_stm32f4_bootloader();

/**
 * @brief Get a thread id by thread name
 */
extern k_tid_t wh_util_thread_get_by_name(char* name);

/**
 * @brief Determine if badge is provisioned
 */
extern bool wh_util_is_provisioned();

#endif