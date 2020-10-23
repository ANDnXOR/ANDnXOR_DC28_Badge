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
#ifndef WH_SYSTEM_H
#define WH_SYSTEM_H

#include "kernel.h"

#define VERSION_INT 27
#define VERSION "v27"
#define BUILD_TIMESTAMP \
  ""__DATE__            \
  " "__TIME__           \
  " PT"

#define SPI_FLASH_MIN_VERSION 24
#define SPI_FLASH_MAX_VERSION 30
#define SPI_FLASH_VERSION_FILENAME "/VERSION"

#define WH_THREAD_PRIORITY_HIGH K_PRIO_COOP(1)
#define WH_THREAD_PRIORITY_MEDIUM K_PRIO_PREEMPT(5)
#define WH_THREAD_PRIORITY_LOW K_PRIO_PREEMPT(9)

#define BADGE_ID_UNKNOWN 0xFFFF
#define BADGE_ID_MAXIMUM 1024

#define WH_PATH_MAX_LEN 128

extern struct k_mutex g_mutex_display_dc;
extern struct k_mutex g_mutex_ui;

#endif